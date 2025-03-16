#pragma once

#include "order.hpp"
#include <iostream>
#include <queue>
#include <vector>

class Book {
  private:
    std::priority_queue<Order> bids; // Max heap for bids
    std::priority_queue<Order, std::vector<Order>, std::greater<Order>>
        asks; // Min heap for asks

  public:
    void addOrder(const Order &order);

    void matchOrder();

    void cancelOrder(int id);

    void printOrderBook() const;

    void modifyOrder(int id, double price, int quantity);

    void printOrderBook() const;

    void saveOrderBookBinary(const std::string &filename) const;

    void loadOrderBookBinary(const std::string &filename);
};