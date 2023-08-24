#include <catch2/catch_test_macros.hpp>

#include "../src/limit.hpp"
#include "../src/limit_tree.hpp"

TEST_CASE( "limit tree insert is correct" ) {
    order_book::LimitTree* lt = new order_book::LimitTree();

    SECTION( "inserting one limit is correct" ) {
        order_book::Limit* l = new order_book::Limit(10);
        lt->Insert(l);

        order_book::Limit* root = lt->GetRoot();
        REQUIRE(root == l);
        REQUIRE(root->color == order_book::BLACK);
        REQUIRE(root->leftChild == lt->GetTNil());
        REQUIRE(root->rightChild == lt->GetTNil());

        delete lt;
    }

    SECTION( "case 2: when uncle is red results in a recolor" ) {
        order_book::Limit* l1 = new order_book::Limit(10);
        order_book::Limit* l2 = new order_book::Limit(5);
        order_book::Limit* l3 = new order_book::Limit(15);
        order_book::Limit* l4 = new order_book::Limit(12);

        lt->Insert(l1);
        lt->Insert(l2);
        lt->Insert(l3);
        lt->Insert(l4);

        order_book::Limit* root = lt->GetRoot();
        REQUIRE(root->color == order_book::BLACK);
        REQUIRE(root->leftChild->color == order_book::BLACK);
        REQUIRE(root->rightChild->rightChild->color == order_book::BLACK);
        REQUIRE(root->rightChild->leftChild->color == order_book::RED);

        delete lt;
    }

    SECTION( "case 3: when uncle is black + triangle results in 2 rotates and a recolor" ) {
        order_book::Limit* l1 = new order_book::Limit(10);
        order_book::Limit* l2 = new order_book::Limit(15);
        order_book::Limit* l3 = new order_book::Limit(12);

        lt->Insert(l1);
        lt->Insert(l2);
        lt->Insert(l3);

        order_book::Limit* root = lt->GetRoot();
        // REQUIRE(root->leftChild == lt->GetTNil());
        REQUIRE(root->color == order_book::BLACK);
        REQUIRE(root->limitPrice == 12);
        REQUIRE(root->leftChild->color == order_book::RED);
        REQUIRE(root->leftChild->limitPrice == 10);
        REQUIRE(root->rightChild->color == order_book::RED);
        REQUIRE(root->rightChild->limitPrice == 15);

        delete lt;
    }

    SECTION( "symmetric case 3: when uncle is black + triangle results in 2 rotates and a recolor" ) {
        order_book::Limit* l1 = new order_book::Limit(10);
        order_book::Limit* l2 = new order_book::Limit(5);
        order_book::Limit* l3 = new order_book::Limit(8);

        lt->Insert(l1);
        lt->Insert(l2);
        lt->Insert(l3);

        order_book::Limit* root = lt->GetRoot();
        // REQUIRE(root->leftChild == lt->GetTNil());
        REQUIRE(root->color == order_book::BLACK);
        REQUIRE(root->limitPrice == 8);
        REQUIRE(root->leftChild->color == order_book::RED);
        REQUIRE(root->leftChild->limitPrice == 5);
        REQUIRE(root->rightChild->color == order_book::RED);
        REQUIRE(root->rightChild->limitPrice == 10);

        delete lt;
    }
}