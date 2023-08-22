#include <catch2/catch_test_macros.hpp>

#include "../src/order.hpp"

TEST_CASE( "order constructors are correct" ) {

    SECTION( "default constructor is correct") {
        order_book::Order o;

        REQUIRE( o.idNumber == 0 );
        REQUIRE( o.buyOrSell == true );
        REQUIRE( o.shares == 0 );
        REQUIRE( o.limit == 0 );
        REQUIRE( o.entryTime == 0 );
        REQUIRE( o.eventTime == 0 );
        REQUIRE( o.nextOrder == nullptr );
        REQUIRE( o.prevOrder == nullptr );
        REQUIRE( o.parentLimit == nullptr );
    }

    SECTION( "orderInfo constructor is correct" ) {
        order_book::Order o({10, false, 10, 10, 10, 10});

        REQUIRE( o.idNumber == 10 );
        REQUIRE( o.buyOrSell == false );
        REQUIRE( o.shares == 10 );
        REQUIRE( o.limit == 10 );
        REQUIRE( o.entryTime == 10 );
        REQUIRE( o.eventTime == 10 );
        REQUIRE( o.nextOrder == nullptr );
        REQUIRE( o.prevOrder == nullptr );
        REQUIRE( o.parentLimit == nullptr );

    }
}
