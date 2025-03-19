import random
import asyncio

class OrderGenerator:
    def __init__(self):
        self.order_types = ['BUY', 'SELL']
        self.price_range = (100, 150)
        self.quantity_range = (1, 10)

    def generate_order(self, current_price):
        """Generate a random order based on market conditions."""
        side = random.choice(self.order_types)

        # Random price close to market price
        price = round(current_price + random.uniform(-1, 1), 2) 
        quantity = random.randint(self.quantity_range[0], self.quantity_range[1])
        return {
            'side': side,
            'price': price,
            'quantity': quantity,
            'order_type': 'LIMIT' if random.random() > 0.3 else 'MARKET'
        }

    async def generate_order_async(self, current_price):
        """Asynchronously generate orders at random intervals."""
        while True:
            # Wait between 1 and 3 seconds so that we do not end up flooding with orders
            await asyncio.sleep(random.uniform(1, 3))
            yield self.generate_order(current_price)
