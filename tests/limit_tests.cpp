#include <catch2/catch_test_macros.hpp>

TEST_CASE("limit default constructor is correct") {
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