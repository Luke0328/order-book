#ifndef LIMIT_H
#define LIMIT_H

namespace crypto_order_book {

    class Order;

    class Limit {
      public:
        int limitPrice;
        int size;
        int totalVolume;
        Limit *parent;
        Limit *leftChild;
        Limit *rightChild;
        Order *headOrder;
        Order *tailOrder;

        Limit();
        Limit(int limitPrice, int size, int totalVolume);

        Order* AddOrder(Order* order);
        void RemoveOrder(Order* order);

        ~Limit();
    };

} // namespace crypto_order_book

#endif
