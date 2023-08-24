#include <iostream>

#include "order.hpp"
#include "limit.hpp"

namespace order_book
{
    
    Limit::Limit()
        : limitPrice(0), size(0), totalVolume(0)
    {
        this->parent = nullptr;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        this->headOrder = nullptr;
        this->tailOrder = nullptr;
    }

    Limit::Limit(int limitPrice)
        : limitPrice(limitPrice), size(0), totalVolume(0)
    {
        this->parent = nullptr;
        this->leftChild = nullptr;
        this->rightChild = nullptr;
        this->headOrder = nullptr;
        this->tailOrder = nullptr;
    }

    Order* Limit::AddOrder(Order* order)
    {
        order->parentLimit = this;
        this->size++;
        this->totalVolume += order->shares;
        if (this->headOrder == nullptr && this->tailOrder == nullptr) {
            this->headOrder = order;
            this->tailOrder = order;
            return order;
        }
        this->tailOrder->nextOrder = order;
        order->prevOrder = this->tailOrder;
        tailOrder = order;

        return order;
    }

    void Limit::RemoveOrder(Order* order)
    {
        if (this->headOrder == order && this->tailOrder == order) {
            this->headOrder = this->tailOrder = nullptr;
        } else if (this->headOrder == order && order->nextOrder) {
            this->headOrder = order->nextOrder;
            order->nextOrder->prevOrder = nullptr;
        } else if (this->tailOrder == order && order->prevOrder) {
            this->tailOrder = order->prevOrder;
            order->prevOrder->nextOrder = nullptr;
        } else {
            order->prevOrder->nextOrder = order->nextOrder;
            order->nextOrder->prevOrder = order->prevOrder;
        }
        this->size--;
        this->totalVolume -= order->shares;
        delete order;
    }


    Limit::~Limit()
    {
        Order* curr = this->headOrder;
        Order* next = nullptr;

        while (curr) {
            next = curr->nextOrder;
            delete curr;
            curr = next;
        }
    }

} // namespace order_book
