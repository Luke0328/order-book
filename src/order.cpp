#include "order.hpp"

namespace order_book {

  Order::Order()
    :Order({0, true, 0, 0, 0, 0})
  {
  }

  Order::Order(OrderInfo order_info)
    : idNumber(order_info.idNumber), buyOrSell(order_info.buyOrSell), shares(order_info.shares), limit(order_info.limit), entryTime(order_info.entryTime),
      eventTime(order_info.eventTime) 
  {
    this->nextOrder = nullptr;
    this->prevOrder = nullptr;
    this->parentLimit = nullptr;
  }

  Order::~Order()
  {
  }

} // namespace order_book
