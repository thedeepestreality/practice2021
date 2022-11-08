import asyncio
import websockets
import serial_asyncio

class OutputProtocol(asyncio.Protocol):
    def connection_made(self, transport):
        self.transport = transport
        print('port opened', transport)
        transport.serial.rts = False  # You can manipulate Serial object via transport
        transport.write(b'Hello, World!\n')  # Write serial data via transport

    def data_received(self, data):
        print('data received', repr(data))

    def connection_lost(self, exc):
        print('port closed')
        self.transport.loop.stop()

async def echo(websocket):
    async for message in websocket:
        await websocket.send("hello")

async def main():
    print("Starting server...")
    async with websockets.serve(echo, "localhost", 2022):
        print("hello")
        loop = asyncio.get_event_loop()
        coro = serial_asyncio.create_serial_connection(loop, OutputProtocol, 'COM10', baudrate=9600)
        transport, protocol = loop.run_until_complete(coro)
        #loop.run_forever()
        #loop.close()
        # await asyncio.Future()  # run forever
        


asyncio.run(main())
