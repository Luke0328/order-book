#include <catch2/catch_test_macros.hpp>

#include "../src/book.hpp"

TEST_CASE( "book constructors are correct" ) {
    
    order_book::Book b;

    REQUIRE( b.GetBestAsk() == nullptr );
    REQUIRE( b.GetBestBid() == nullptr );

}

TEST_CASE( "book Add is correct" ) {
    
    order_book::Book* b = new order_book::Book();

    SECTION( "adding one buy order" ) {

        order_book::OrderInfo buy_order_1 = {1, true, 25, 10, 10, 10};

        b->Add(buy_order_1);

        REQUIRE( b->GetVolumeAtLimit(10) == 25);
        REQUIRE( b->GetBestBid()->idNumber == 1 );
        REQUIRE( b->GetBestBid()->shares == 25 );
        REQUIRE( b->GetBestBid()->limit == 10 );

        delete b;
    }

    SECTION( "adding two buy orders at same limit results in first order as best bid" ) {

        order_book::OrderInfo buy_order_1 = {1, true, 25, 10, 10, 10};
        order_book::OrderInfo buy_order_2 = {2, true, 50, 10, 11, 11};

        b->Add(buy_order_1);
        b->Add(buy_order_2);

        REQUIRE( b->GetVolumeAtLimit(10) == 75);
        REQUIRE( b->GetBestBid()->idNumber == 1 );
        REQUIRE( b->GetBestBid()->shares == 25 );
        REQUIRE( b->GetBestBid()->limit == 10 );

        delete b;
    }

    SECTION( "adding two buy orders with different limits results in correct best bid" ) {

        order_book::OrderInfo buy_order_1 = {1, true, 25, 10, 10, 10};
        order_book::OrderInfo buy_order_2 = {2, true, 50, 15, 11, 11};

        b->Add(buy_order_1);
        b->Add(buy_order_2);

        REQUIRE( b->GetVolumeAtLimit(10) == 25);
        REQUIRE( b->GetVolumeAtLimit(15) == 50);
        REQUIRE( b->GetBestBid()->idNumber == 2 );
        REQUIRE( b->GetBestBid()->shares == 50 );
        REQUIRE( b->GetBestBid()->limit == 15 );

        delete b;
    }

    SECTION( "adding one sell order" ) {

        order_book::OrderInfo sell_order_1 = {1, false, 25, 10, 10, 10};

        b->Add(sell_order_1);

        REQUIRE( b->GetVolumeAtLimit(10) == 25);
        REQUIRE( b->GetBestAsk()->idNumber == 1 );
        REQUIRE( b->GetBestAsk()->shares == 25 );
        REQUIRE( b->GetBestAsk()->limit == 10 );

        delete b;
    }

    SECTION( "adding two sell orders at same limit results in first order as best sell" ) {

        order_book::OrderInfo sell_order_1 = {1, false, 25, 10, 10, 10};
        order_book::OrderInfo sell_order_2 = {2, false, 50, 10, 11, 11};

        b->Add(sell_order_1);
        b->Add(sell_order_2);

        REQUIRE( b->GetVolumeAtLimit(10) == 75);
        REQUIRE( b->GetBestAsk()->idNumber == 1 );
        REQUIRE( b->GetBestAsk()->shares == 25 );
        REQUIRE( b->GetBestAsk()->limit == 10 );

        delete b;
    }

    SECTION( "adding two sell orders with different limits results in correct best sell" ) {

        order_book::OrderInfo sell_order_1 = {1, false, 25, 10, 10, 10};
        order_book::OrderInfo sell_order_2 = {2, false, 50, 5, 11, 11};

        b->Add(sell_order_1);
        b->Add(sell_order_2);

        REQUIRE( b->GetVolumeAtLimit(10) == 25);
        REQUIRE( b->GetVolumeAtLimit(5) == 50);
        REQUIRE( b->GetBestAsk()->idNumber == 2 );
        REQUIRE( b->GetBestAsk()->shares == 50 );
        REQUIRE( b->GetBestAsk()->limit == 5 );

        delete b;
    }

}

TEST_CASE( "book Delete is correct" ) {

    order_book::Book* b = new order_book::Book();

    SECTION( "deleting one order is correct" ) {

        order_book::OrderInfo buy_order_1 = {1, true, 25, 10, 10, 10};
        b->Add(buy_order_1);
        b->Delete(1);

        REQUIRE( b->GetVolumeAtLimit(10) == 0 );
        REQUIRE( b->GetBestBid() == nullptr );

        delete b;
    }

    SECTION( "deleting order updates best bid" ) {

        order_book::OrderInfo buy_order_1 = {1, true, 25, 10, 10, 10};
        order_book::OrderInfo buy_order_2 = {2, true, 50, 10, 11, 11};

        b->Add(buy_order_1);
        b->Add(buy_order_2);
        b->Delete(1);

        REQUIRE( b->GetVolumeAtLimit(10) == 50 );
        REQUIRE( b->GetBestBid() != nullptr );
        REQUIRE( b->GetBestBid()->idNumber == 2 );
        REQUIRE( b->GetBestBid()->shares == 50 );

        delete b;
    }

}

TEST_CASE( "book Execute is correct" ) {

    order_book::Book* b = new order_book::Book();

    SECTION( "deleting one order is correct" ) {

        order_book::OrderInfo buy_order_1 = {1, true, 25, 10, 10, 10};
        b->Add(buy_order_1);
        b->Execute(true);

        REQUIRE( b->GetVolumeAtLimit(10) == 0 );
        REQUIRE( b->GetBestBid() == nullptr );

        delete b;
    }

    SECTION( "deleting order updates best bid" ) {

        order_book::OrderInfo buy_order_1 = {1, true, 25, 10, 10, 10};
        order_book::OrderInfo buy_order_2 = {2, true, 50, 10, 11, 11};

        b->Add(buy_order_1);
        b->Add(buy_order_2);
        b->Execute(true);

        REQUIRE( b->GetVolumeAtLimit(10) == 50 );
        REQUIRE( b->GetBestBid() != nullptr );
        REQUIRE( b->GetBestBid()->idNumber == 2 );
        REQUIRE( b->GetBestBid()->shares == 50 );

        delete b;
    }

}