#include "../include/generator.hpp"
#include <chrono>
#include <random>

OrderType generateRandomOrderType() {
    double prob = 0.7;
    double rand_num = (double)rand() / RAND_MAX;
    return (rand_num < prob) ? OrderType::LIMIT : OrderType::MARKET;
}

OrderSide generateRandomOrderSide() {
    double prob = 0.55;
    double rand_num = (double)rand() / RAND_MAX;
    return (rand_num < prob) ? OrderSide::BUY : OrderSide::SELL;
}

OrderExeType generateRandomOrderExeType(OrderType type) {
    double prob_GTC = 0.8;
    double prob_IOC = 0.9;
    double prob_FOK = 1.0;
    double rand_num = (double)rand() / RAND_MAX;
    if (type == OrderType::LIMIT) {
        if (rand_num < prob_GTC)
            return OrderExeType::GTC;
        return (rand_num < prob_IOC) ? OrderExeType::IOC : OrderExeType::FOK;
    } else {
        return (rand_num < prob_FOK) ? OrderExeType::IOC : OrderExeType::FOK;
    }
}

// Normal distribution for price
double generateRandomPrice(double mid_price, double vol, OrderSide side) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::normal_distribution<> d(mid_price, vol);

    double price;
    do {
        price = d(gen);
    } while ((side == OrderSide::BUY && price >= mid_price) ||
             (side == OrderSide::SELL && price <= mid_price));

    return price;
}

// Normal distribution for quantity
int generateRandomQuantity() {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::lognormal_distribution<double> size_dist(1.5, 0.5);
    return std::max(1, static_cast<int>(size_dist(gen)));
}

Order generateRandomOrder(int id, std::string symbol, double mid_price,
                          double vol) {
    OrderType type = generateRandomOrderType();
    OrderSide side = generateRandomOrderSide();
    OrderExeType exeType = generateRandomOrderExeType(type);
    int quantity = generateRandomQuantity();
    OrderStatus status = OrderStatus::OPEN;

    long long timestamp =
        std::chrono::system_clock::now().time_since_epoch().count();

    double price = 0.0;

    if (type == OrderType::MARKET) {
        price = mid_price;
    } else {
        price = generateRandomPrice(mid_price, vol, side);
    }

    return Order(id, timestamp, symbol, price, quantity, side, exeType, status,
                 type);
}