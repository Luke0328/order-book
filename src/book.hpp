#ifndef BOOK_H
#define BOOK_H

#include <unordered_map>

#include "order.hpp"
#include "limit.hpp"

namespace order_book {

    class Book {
        private:
            Limit *buyTree;
            Limit *sellTree;
            Limit *lowestSell;
            Limit *highestBuy;

            std::unordered_map<int, Order*> order_map;
            std::unordered_map<double, Limit*> limit_map;

            // HELPER FUNCTIONS
            Order *CreateOrder(OrderInfo order_info);
            Limit *GetOrCreateLimit(Order* order);
            Limit *InsertLimit(Limit* limit, bool BuyOrSell);

        public:
            Book();

            void Add(OrderInfo order_info); // Add order to order book
            // void Cancel(int order_id, int shares);
            void Delete(int order_id); // Delete order from anywhere in order book
            void Execute(bool buyOrSell); // Execute order from inside the book
            int GetVolumeAtLimit(int limit_price); // Get volumne at specified limit price
            Order* GetBestBid(); // Get the Best Bid - oldest buy order at highest buy price
            Order* GetBestAsk(); // Get the Best Ask - oldest sell order at lowest sell price
            
            void DestroyRecursive(Limit* limit);
            ~Book();
    };

} // namespace order_book

#endif
