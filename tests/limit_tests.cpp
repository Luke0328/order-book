#include <catch2/catch_test_macros.hpp>

#include "../src/order.hpp"
#include "../src/limit.hpp"

TEST_CASE("limit constructors are correct") {

    SECTION( "default constructor is correct" ) {
        order_book::Limit* l = new order_book::Limit();

        REQUIRE( l->limitPrice == 0 );
        REQUIRE( l->size == 0 );
        REQUIRE( l->totalVolume == 0 );
        REQUIRE( l->parent == nullptr );
        REQUIRE( l->leftChild == nullptr );
        REQUIRE( l->rightChild == nullptr );
        REQUIRE( l->headOrder == nullptr );
        REQUIRE( l->tailOrder == nullptr );

        delete l;
    }

    SECTION( "parameterized constructor is correct" ) {
        order_book::Limit* l = new order_book::Limit(10);

        REQUIRE( l->limitPrice == 10 );
        REQUIRE( l->size == 0 );
        REQUIRE( l->totalVolume == 0 );
        REQUIRE( l->parent == nullptr );
        REQUIRE( l->leftChild == nullptr );
        REQUIRE( l->rightChild == nullptr );
        REQUIRE( l->headOrder == nullptr );
        REQUIRE( l->tailOrder == nullptr );

        delete l;
    }

}

TEST_CASE( "limit AddOrder is correct" ) {

    order_book::Limit* l = new order_book::Limit(10);

    SECTION( "adding one order" ) {
        order_book::Order* o1 = new order_book::Order({10, true, 10, 10, 10, 10});
    
        l->AddOrder(o1);

        REQUIRE(o1->parentLimit == l);

        REQUIRE(l->size == 1);
        REQUIRE(l->totalVolume == 10);
        REQUIRE(l->headOrder == o1);
        REQUIRE(l->tailOrder == o1);
        REQUIRE(l->leftChild == nullptr);
        REQUIRE(l->rightChild == nullptr);
        REQUIRE(l->parent == nullptr);

        delete l;
    }

    SECTION( "adding two orders" ) {

        order_book::Order* o1 = new order_book::Order({10, true, 10, 10, 10, 10});
        order_book::Order* o2 = new order_book::Order({11, true, 20, 10, 10, 10});

        l->AddOrder(o1);
        l->AddOrder(o2);

        REQUIRE(o1->parentLimit == l);
        REQUIRE(o2->parentLimit == l);

        REQUIRE(l->size == 2);
        REQUIRE(l->totalVolume == 10 + 20);
        REQUIRE(l->headOrder == o1);
        REQUIRE(l->tailOrder == o2);
        REQUIRE(l->leftChild == nullptr);
        REQUIRE(l->rightChild == nullptr);
        REQUIRE(l->parent == nullptr);

        REQUIRE(o1->nextOrder == o2);
        REQUIRE(o2->prevOrder == o1);

        delete l;
    }

}

TEST_CASE( "limit RemoveOrder is correct" ) {

    order_book::Limit* l = new order_book::Limit(10);

    SECTION( "removing one order" ) {

        order_book::Order* o1 = new order_book::Order({10, true, 10, 10, 10, 10});
        order_book::Order* o2 = new order_book::Order({11, true, 20, 10, 10, 10});
        l->AddOrder(o1);
        l->AddOrder(o2);

        l->RemoveOrder(o1);

        REQUIRE(l->size == 1);
        REQUIRE(l->totalVolume == 20);
        REQUIRE(l->headOrder == o2);
        REQUIRE(l->tailOrder == o2);

        delete l;
    }

    SECTION( "removing two orders" ) {
 
        order_book::Order* o1 = new order_book::Order({10, true, 10, 10, 10, 10});
        order_book::Order* o2 = new order_book::Order({11, true, 20, 10, 10, 10});
        l->AddOrder(o1);
        l->AddOrder(o2);

        l->RemoveOrder(o1);
        l->RemoveOrder(o2);

        REQUIRE(l->size == 0);
        REQUIRE(l->totalVolume == 0);
        REQUIRE(l->headOrder == nullptr);
        REQUIRE(l->tailOrder == nullptr);

        delete l;
    }

}