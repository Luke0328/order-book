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

    Limit::Limit(int limitPrice, int size, int totalVolume)
        : limitPrice(limitPrice), size(size), totalVolume(totalVolume)
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
        if (!headOrder && !tailOrder) {
            headOrder = order;
            tailOrder = order;
            return order;
        }
        this->tailOrder->nextOrder = order;
        order->prevOrder = this->tailOrder;
        tailOrder = order;

        this->size++;
        this->totalVolume += order->shares;

        return order;
    }

    void Limit::RemoveOrder(Order* order)
    {
        if (this->headOrder == order && this->tailOrder == order) {
            headOrder = tailOrder = nullptr;
        } else if (this->headOrder == order && order->nextOrder) {
            this->headOrder = order->nextOrder;
            order->nextOrder->prevOrder = nullptr;
        } else if (this->tailOrder == order && order->prevOrder) {
            this->tailOrder = order->prevOrder;
            order->prevOrder->nextOrder = nullptr;
        }
        this->size--;
        this->totalVolume -= order->shares;
        delete order;
    }


    Limit::~Limit()
    {
        Order* curr = this->headOrder;
        Order* next;

        while (curr) {
            next = curr->nextOrder;
            delete curr;
            curr = next;
        }
    }

} // namespace order_book
