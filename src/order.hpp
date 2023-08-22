#ifndef ORDER_H
#define ORDER_H


namespace order_book {

    class Limit;

    struct OrderInfo {
        int idNumber;
        bool buyOrSell; // buy T, sell F
        int shares;
        int limit;
        int entryTime;
        int eventTime;
    };

    class Order {
        public:
            int idNumber;
            bool buyOrSell; // buy T, sell F
            int shares;
            int limit;
            int entryTime;
            int eventTime;
            Order *nextOrder;
            Order *prevOrder;
            Limit *parentLimit;

            Order();
            Order(OrderInfo order_info);

            ~Order();
    };

} // namespace order_book

#endif
