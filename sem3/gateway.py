import asyncio
import websockets
import time

async def echo(websocket):
    async for message in websocket:
        await websocket.send("hello")


async def main():
    print("Starting server...")
    async with websockets.serve(echo, "localhost", 2022):
        print("hello")
        await asyncio.Future()  # run forever

asyncio.run(main())
