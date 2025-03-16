#include "../include/book.hpp"
#include <cstring>
#include <fstream>
#include <iostream>

void Book::addOrder(const Order &order) {
    if (order.getSide() == OrderSide::BUY) {
        bids.push(order);
    } else {
        asks.push(order);
    }
}

// Supports partial fills
void Book::matchOrder() {
    while (!bids.empty() && !asks.empty() &&
           bids.top().getPrice() >= asks.top().getPrice()) {
        Order bid = bids.top();
        Order ask = asks.top();

        if (bid.getQuantity() == ask.getQuantity()) {
            std::cout << "Matched order: " << bid.getSymbol() << " "
                      << bid.getQuantity() << " @ " << bid.getPrice() << " "
                      << (bid.getSide() == OrderSide::BUY ? "BUY" : "SELL")
                      << std::endl;
            bids.pop();
            asks.pop();
        } else if (bid.getQuantity() > ask.getQuantity()) {
            std::cout << "Matched order: " << bid.getSymbol() << " "
                      << ask.getQuantity() << " @ " << bid.getPrice() << " "
                      << (bid.getSide() == OrderSide::BUY ? "BUY" : "SELL")
                      << std::endl;
            bid.setQuantity(bid.getQuantity() - ask.getQuantity());
            asks.pop();
        } else {
            std::cout << "Matched order: " << bid.getSymbol() << " "
                      << bid.getQuantity() << " @ " << bid.getPrice() << " "
                      << (bid.getSide() == OrderSide::BUY ? "BUY" : "SELL")
                      << std::endl;
            ask.setQuantity(ask.getQuantity() - bid.getQuantity());
            bids.pop();
        }
    }
}

void Book::cancelOrder(int id) {
    std::cout << "Not needed for now, need to develop this. " << id
              << std::endl;
}

void Book::printOrderBook() const {
    std::cout << "Bids: " << std::endl;
    std::priority_queue<Order> tempBids = bids;
    while (!tempBids.empty()) {
        tempBids.top().print();
        tempBids.pop();
    }

    std::cout << "Asks: " << std::endl;
    std::priority_queue<Order, std::vector<Order>, std::greater<Order>>
        tempAsks = asks;
    while (!tempAsks.empty()) {
        tempAsks.top().print();
        tempAsks.pop();
    }
}

void Book::modifyOrder(int id, double price, int quantity) {
    std::cout << "Not needed for now, need to develop this. " << id << " "
              << price << " " << quantity << std::endl;
}

void Book::saveOrderBookBinary(const std::string &filename) const {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    // Write bids
    std::priority_queue<Order> tempBids = bids;
    while (!tempBids.empty()) {
        tempBids.top().writeToBinaryFile(file);
        tempBids.pop();
    }

    // Write asks
    std::priority_queue<Order, std::vector<Order>, std::greater<Order>>
        tempAsks = asks;
    while (!tempAsks.empty()) {
        tempAsks.top().writeToBinaryFile(file);
        tempAsks.pop();
    }

    file.close();
}

void Book::loadOrderBookBinary(const std::string &filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    while (file.peek() != EOF) {
        Order order = Order::readFromBinaryFile(file);
        addOrder(order);
    }

    file.close();
}