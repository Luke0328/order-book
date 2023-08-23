#ifndef LIMIT_H
#define LIMIT_H

namespace order_book {

    class Order;

    class Limit {
      public:
        int limitPrice;
        int size; // number of orders at this limit
        int totalVolume; // total number of shares at this limit
        Limit *parent;
        Limit *leftChild;
        Limit *rightChild;
        Order *headOrder;
        Order *tailOrder;

        Limit();
        Limit(int limitPrice);

        Order* AddOrder(Order* order);
        void RemoveOrder(Order* order);

        ~Limit();
    };

} // namespace order_book

#endif
