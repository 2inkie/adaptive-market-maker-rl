#pragma once

#include <string>

enum class OrderSide { SELL, BUY };

enum class OrderExeType {
    GTC, // Good till cancelled
    IOC, // Immediate or cancel
    FOK  // Fill or kill
};

enum class OrderType { LIMIT, MARKET };

enum class OrderStatus { OPEN, FILLED, CANCELLED };

// Order class
class Order {
  private:
    int id;
    int quantity; // Probably at some point I can try to do this with non
                  // integer values
    std::string symbol;
    double price;
    long long timestamp;
    OrderSide side;
    OrderExeType exeType;
    OrderStatus status;
    OrderType type;

  public:
    Order(int id, long long timestamp, std::string symbol, double price,
          int quantity, OrderSide side, OrderExeType exeType,
          OrderStatus status, OrderType type)
        : id(id), timestamp(timestamp), symbol(symbol), price(price),
          quantity(quantity), side(side), exeType(exeType), status(status),
          type(type) {}

    // Getters
    int getId() const { return id; }
    long long getTimestamp() const { return timestamp; }
    std::string getSymbol() const { return symbol; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    OrderSide getSide() const { return side; }
    OrderExeType getExeType() const { return exeType; }
    OrderStatus getStatus() const { return status; }
    OrderType getType() const { return type; }

    // Setters -
    void setPrice(double price) { this->price = price; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    void setSide(OrderSide side) { this->side = side; }
    void setExeType(OrderExeType exeType) { this->exeType = exeType; }
    void setStatus(OrderStatus status) { this->status = status; }
    void setType(OrderType type) { this->type = type; }

    void writeToBinaryFile(std::ofstream &file) const;

    static Order readFromBinaryFile(std::ifstream &file);

    void print() const;
};