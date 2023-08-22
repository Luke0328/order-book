#include "order.hpp"
#include "limit.hpp"
#include "book.hpp"

namespace order_book {

    Book::Book()
    {
        this->buyTree = nullptr;
        this->sellTree = nullptr;
        this->lowestSell = nullptr;
        this->highestBuy = nullptr;
    }

    void Book::Add(OrderInfo order_info)
    {
        Order* new_order = this->CreateOrder(order_info);
        Limit* limit = this->GetOrCreateLimit(new_order);
        limit->AddOrder(new_order);
    }

    void Book::Delete(int order_id) 
    {
        if (this->order_map.find(order_id) == order_map.end()) {
            return;
        }
        Order* order = this->order_map[order_id];
        Limit* parent_limit = this->limit_map[order->limit];
        parent_limit->RemoveOrder(order);
        this->order_map.erase(order_id);
    }

    void Book::Execute(int order_id)
    {
        bool buyOrSell = order_map[order_id]->buyOrSell;
        Order* order_to_execute;
        if (buyOrSell) {
            order_to_execute = this->GetBestBid();
        } else {
            order_to_execute = this->GetBestAsk();
        }

        if (order_to_execute == nullptr) {
            return;
        }
        
        Limit *parentLimit = order_to_execute->parentLimit;
        parentLimit->size--;
        parentLimit->totalVolume -= order_to_execute->shares;

        parentLimit->headOrder = order_to_execute->nextOrder;
        order_to_execute->nextOrder->prevOrder = nullptr;

        delete order_to_execute;
    }

    int Book::GetVolumeAtLimit(int limit_price)
    {
        if (this->limit_map.find(limit_price) != this->limit_map.end()) {
            return this->limit_map[limit_price]->totalVolume;
        }
        return -1;
    }

    Order* Book::GetBestBid() 
    {
        if (this->highestBuy == nullptr) {
            return nullptr;
        }
        return this->highestBuy->headOrder;
    }

    Order* Book::GetBestAsk() 
    {
        if (this->lowestSell == nullptr) {
            return nullptr;
        }
        return this->lowestSell->headOrder;
    }

    Order* Book::CreateOrder(OrderInfo order_info) {
        Order* new_order = new Order(order_info);
        this->order_map[new_order->idNumber] = new_order;
        return new_order;
    }

    Limit* Book::GetOrCreateLimit(Order* order) 
    {
        Limit* ret_limit = nullptr;
        if (limit_map.find(order->limit) != limit_map.end()) {
            ret_limit = this->limit_map[order->limit];
        } else {
            Limit* new_limit = new Limit(order->limit, 0, 0);
            this->limit_map[order->limit] = new_limit; // add to map
            this->InsertLimit(new_limit, order->buyOrSell);
            ret_limit = new_limit;
        }
        return ret_limit;
    }

    Limit* Book::InsertLimit(Limit* limit, bool BuyOrSell)
    {
        Limit* curr;
        if (BuyOrSell) { // buy order
            if (!this->buyTree) {
                this->buyTree = limit;
                return limit;
            }
            curr = this->buyTree;
            if (!this->highestBuy || limit->limitPrice > this->highestBuy->limitPrice) {
                this->highestBuy = limit;
            }
        } else { // sell order
            if (!this->sellTree) {
                this->sellTree = limit;
                return limit;
            }
            curr = this->sellTree;
            if (!this->lowestSell || limit->limitPrice < this->lowestSell->limitPrice) {
                this->lowestSell = limit;
            }
        }

        if (!curr) {
            curr = limit;
            return limit;
        }

        Limit* prev = nullptr;
        while (curr) {
            prev = curr;
            if (limit->limitPrice <= curr->limitPrice) {
                curr = curr->leftChild;
            } else {
                curr = curr->rightChild;
            }
        }
        if (limit->limitPrice <= prev->limitPrice) {
            prev->leftChild = limit;
        } else {
            prev->rightChild = limit;
        }
        limit->parent = prev;

        return limit;
    }

    void Book::DestroyRecursive(Limit *limit)
    {
        if (limit) {
            DestroyRecursive(limit->leftChild);
            DestroyRecursive(limit->rightChild);
            delete limit;
        }
    }

    Book::~Book()
    {
        DestroyRecursive(this->buyTree);
        DestroyRecursive(this->sellTree);
    }

} // namespace cypto_order_book
