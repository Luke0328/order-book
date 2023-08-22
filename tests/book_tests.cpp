#include <catch2/catch_test_macros.hpp>

#include "../src/book.hpp"

TEST_CASE( "book constructors are correct" ) {
    
    // order_book::Book b;

    // REQUIRE( b.GetBestAsk() == nullptr );
    // REQUIRE( b.GetBestBid() == nullptr );

}

// TEST_CASE( "book Add is correct" ) {
    
//     order_book::Book* b = new order_book::Book();

//     SECTION( "Add one order" ) {

//         order_book::OrderInfo buy_order_1 = {1, true, 25, 10, 10, 10};

//         b->Add(buy_order_1);

//         REQUIRE( b->GetVolumeAtLimit(10) == 25);
//         REQUIRE( b->GetBestBid()->idNumber == 1 );
//         REQUIRE( b->GetBestBid()->shares == 25 );
//         REQUIRE( b->GetBestBid()->limit == 10 );
//     }

// }