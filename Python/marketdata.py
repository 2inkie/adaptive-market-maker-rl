import asyncio
import websockets
import json

class MarketDataClient:
    def __init__(self, pair, url = "wss://ws.kraken.com"):
        self.uri = url
        self.pair = pair
        self.websocket = None
        self.subscriptions = [{"event": "subscribe", "pair": self.pair, "subscription": {"name": "trade"}}]


    async def subscribe(self, websocket):
        for sub in self.subscriptions:
            await websocket.send(json.dumps(sub))

    async def connect(self):
        async with websockets.connect(self.uri) as websocket:
            await self.subscribe(websocket)
            print(f"Connected to {self.uri}")

            while True:
                data = await websocket.recv()
                asyncio.create_task(self.process_data(data))

    async def process_data(self, data):
        """Asynchronously process and print relevant trade data."""
        try:
            parsed_data = json.loads(data)

            if isinstance(parsed_data, dict):
                if parsed_data.get("event") == "heartbeat":
                    return
                print(f"System Message: {json.dumps(parsed_data, indent=2)}")

            elif isinstance(parsed_data, list) and len(parsed_data) > 3:
                channel_id = parsed_data[0]
                trades = parsed_data[1]
                pair = parsed_data[3]

                for trade in trades:
                    price, volume, timestamp, side, order_type, _ = trade
                    side = "BUY" if side == "b" else "SELL"

                    print(f"TRADE | {pair} | {side} | Price: {price} | Volume: {volume} | Time: {timestamp} | Type: {order_type} | ID: {channel_id}")

        except json.JSONDecodeError:
            print(f"Received non-JSON message: {data}")

async def main():
    client = MarketDataClient(["XBT/USD"])
    await client.connect()

asyncio.run(main())