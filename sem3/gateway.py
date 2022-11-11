import serial
import asyncio as aio
import websockets

glob = {}

async def read_ws(websocket, aio_loop):
    try:
        str = await aio.wait_for(websocket.recv(), 0.1)
        print("sock: :",str)
        await aio.ensure_future(glob["q_ws"].put(str), loop = aio_loop)
    except aio.TimeoutError:
        pass

async def send_ws(websocket):
    try:
        str = await aio.wait_for(glob["q_ser"].get(), 0.1)
        print("serial: :", str)
        await websocket.send(str.decode('UTF-8'))
    except aio.TimeoutError:
        pass

async def echo(websocket):
    loop = aio.get_event_loop()
    while True:
        await read_ws(websocket, loop)
        await send_ws(websocket)
        
async def serial_read():
    glob["q_ws"] = aio.Queue()
    glob["q_ser"] = aio.Queue()
    port = serial.Serial('COM10', 9600, timeout=0.1)
    loop = aio.get_event_loop()
    while True:
        try:
            str = await aio.wait_for(glob["q_ws"].get(), 0.1)
            str = str.encode()
            str = str[0:3]
            print(f"q_ws: {str}")
            port.write(str)
        except aio.TimeoutError:
            pass

        str = port.readline()
        if (len(str) == 0):
            await aio.sleep(0.1)
            continue
        print(str)
        aio.ensure_future(glob["q_ser"].put(str), loop=loop)

async def main():
    async with websockets.serve(echo, "localhost", 2022):
        print("hello")
        await aio.gather(serial_read())

aio.run(main())