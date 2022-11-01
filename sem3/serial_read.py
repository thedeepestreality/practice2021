import serial
import asyncio as aio
import websockets

q = aio.Queue()

async def echo(websocket):
    while True:
        str = await q.get()
        print("sock: :",str)
        await websocket.send(str.decode('UTF-8'))

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