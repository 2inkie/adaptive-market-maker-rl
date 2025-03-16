#pragma once

#include "order.hpp"

OrderType generateRandomOrderType();
OrderSide generateRandomOrderSide();
OrderExeType generateRandomOrderExeType(OrderType type);
double generateRandomPrice(double mid_price, double vol, OrderSide side);
int generateRandomQuantity();

Order generateRandomOrder(int id, long long timestamp, std::string symbol,
                          double mid_price, double vol);