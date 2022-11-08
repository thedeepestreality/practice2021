import serial
import asyncio as aio
import websockets

q = aio.Queue()

async def read_ws(websocket, aio_loop):
    try:
        str = await aio.wait_for(websocket.recv(), 0.5)
        print("sock: :",str)
        aio.ensure_future(q.put(str), loop = aio_loop)
    except aio.TimeoutError:
        print('no sock data')

async def send_ws(websocket):
    try:
        str = await aio.wait_for(q.get(), 0.5)
        print("serial: :", str)
        await websocket.send(str.decode('UTF-8'))
        #await websocket.send(str)
    except aio.TimeoutError:
        print('no ser data')
           

async def echo(websocket):
    loop = aio.get_event_loop()
    while True:
        await read_ws(websocket, loop)
        await send_ws(websocket)
        
async def serial_read():
    port = serial.Serial('COM10', 9600, timeout=1)
    loop = aio.get_event_loop()
    while True:
        str = port.readline()
        if (len(str) > 0):
            print(str)
        aio.ensure_future(q.put(str), loop=loop)
        await aio.sleep(1)


async def main():
    async with websockets.serve(echo, "localhost", 2022):
        print("hello")
        await aio.gather(serial_read())

aio.run(main())