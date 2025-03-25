#include "../include/order.hpp"
#include <cstring>
#include <fstream>
#include <iostream>

Order::Order(int id, long long timestamp, std::string symbol, double price,
             int quantity, OrderSide side, OrderExeType exeType,
             OrderStatus status, OrderType type)
    : id(id), timestamp(timestamp), symbol(symbol), price(price),
      quantity(quantity), side(side), exeType(exeType), status(status),
      type(type) {}

// Getters
int Order::getId() const { return id; }
long long Order::getTimestamp() const { return timestamp; }
std::string Order::getSymbol() const { return symbol; }
double Order::getPrice() const { return price; }
int Order::getQuantity() const { return quantity; }
OrderSide Order::getSide() const { return side; }
OrderExeType Order::getExeType() const { return exeType; }
OrderStatus Order::getStatus() const { return status; }
OrderType Order::getType() const { return type; }

// Setters
void Order::setPrice(double price) { this->price = price; }
void Order::setQuantity(int quantity) { this->quantity = quantity; }
void Order::setSide(OrderSide side) { this->side = side; }
void Order::setExeType(OrderExeType exeType) { this->exeType = exeType; }
void Order::setStatus(OrderStatus status) { this->status = status; }
void Order::setType(OrderType type) { this->type = type; }

// Print order
void Order::print() const {
    std::cout << "Order ID: " << id << ", Symbol: " << symbol
              << ", Price: " << price << ", Quantity: " << quantity
              << ", Side: " << (side == OrderSide::BUY ? "BUY" : "SELL")
              << ", ExeType: "
              << (exeType == OrderExeType::GTC   ? "GTC"
                  : exeType == OrderExeType::IOC ? "IOC"
                                                 : "FOK")
              << ", Type: " << (type == OrderType::LIMIT ? "LIMIT" : "MARKET")
              << ", Status: "
              << (status == OrderStatus::OPEN     ? "OPEN"
                  : status == OrderStatus::FILLED ? "FILLED"
                                                  : "CANCELLED")
              << ", Timestamp: " << timestamp << std::endl;
}

// Write order to binary file.
void Order::writeToBinaryFile(std::ofstream &file) const {
    file.write(reinterpret_cast<const char *>(&id), sizeof(id));
    file.write(reinterpret_cast<const char *>(&timestamp), sizeof(timestamp));
    file.write(symbol.c_str(), symbol.size());
    file.write(reinterpret_cast<const char *>(&price), sizeof(price));
    file.write(reinterpret_cast<const char *>(&quantity), sizeof(quantity));
    file.write(reinterpret_cast<const char *>(&side), sizeof(side));
    file.write(reinterpret_cast<const char *>(&exeType), sizeof(exeType));
    file.write(reinterpret_cast<const char *>(&status), sizeof(status));
    file.write(reinterpret_cast<const char *>(&type), sizeof(type));
}

// Read order from binary file
Order Order::readFromBinaryFile(std::ifstream &file) {
    int id;
    long long timestamp;
    std::string symbol;
    double price;
    int quantity;
    OrderSide side;
    OrderExeType exeType;
    OrderStatus status;
    OrderType type;

    file.read(reinterpret_cast<char *>(&id), sizeof(id));
    file.read(reinterpret_cast<char *>(&timestamp), sizeof(timestamp));

    char c;
    while (file.get(c) && c != '\0') {
        symbol += c;
    }

    file.read(reinterpret_cast<char *>(&price), sizeof(price));
    file.read(reinterpret_cast<char *>(&quantity), sizeof(quantity));
    file.read(reinterpret_cast<char *>(&side), sizeof(side));
    file.read(reinterpret_cast<char *>(&exeType), sizeof(exeType));
    file.read(reinterpret_cast<char *>(&status), sizeof(status));
    file.read(reinterpret_cast<char *>(&type), sizeof(type));

    return Order(id, timestamp, symbol, price, quantity, side, exeType, status,
                 type);
}