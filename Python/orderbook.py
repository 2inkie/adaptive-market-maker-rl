from collections import deque

class OrderBook:
    def __init__(self):
        self.buy_orders = deque()
        self.sell_orders = deque()

    def add_order(self, order):
        """Add an order to the appropriate side of the order book."""
        if order['side'] == 'BUY':
            self.buy_orders.append(order)
            self.buy_orders = deque(sorted(self.buy_orders, key=lambda x: x['price'], reverse=True))
        else:
            self.sell_orders.append(order)
            self.sell_orders = deque(sorted(self.sell_orders, key=lambda x: x['price']))

    def display_orders(self):
        """Display current orders."""
        print("Buy Orders:")
        for order in self.buy_orders:
            print(order)
        print("Sell Orders:")
        for order in self.sell_orders:
            print(order)
