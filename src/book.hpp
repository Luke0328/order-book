#ifndef BOOK_H
#define BOOK_H

#include <unordered_map>

#include "order.hpp"
#include "limit.hpp"

namespace crypto_order_book {

    class Book {
        private:
            Limit *buyTree;
            Limit *sellTree;
            Limit *lowestSell;
            Limit *highestBuy;

            std::unordered_map<int, Order*> order_map;
            std::unordered_map<double, Limit*> limit_map;

            Order *CreateOrder(OrderInfo order_info);
            Limit *GetOrCreateLimit(Order* order);
            Limit *InsertLimit(Limit* limit, bool BuyOrSell);

        public:
            void Add(OrderInfo order_info);
            void Cancel(int order_id, int shares);
            void Delete(int order_id);
            void Execute(int order_id);
            int GetVolumeAtLimit(int limit_price);
            Order* GetBestBid();
            Order* GetBestOffer();
            
            Book();

            void DestroyRecursive(Limit* limit);
            ~Book();
    };

} // namespace crypto_order_book

#endif
