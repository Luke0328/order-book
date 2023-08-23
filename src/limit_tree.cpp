#include "limit.hpp"
#include "limit_tree.hpp"

namespace order_book {

    LimitTree::LimitTree()
    {
        this->root = nullptr;
    }

    void LimitTree::LeftRotate(Limit* node)
    {
        Limit* new_root = node->rightChild; // new local root

        new_root->parent = node->parent;
        // if there were no nodes above the old root, the new node is the new global root
        if (node->parent == nullptr) {
            this->root = new_root;
        } else if (node->parent->leftChild == node) {
            node->parent->leftChild = new_root;
        } else if (node->parent->rightChild == node) {
            node->parent->rightChild = new_root;
        }

        // attach new root's left subtree as right child of old root
        node->rightChild = new_root->leftChild;
        if (new_root->leftChild != nullptr) {
            node->rightChild->parent = node;
        }

        // make old root left child of new root
        new_root->leftChild = node;
        node->parent = new_root;
    }

    void LimitTree::RightRotate(Limit* node) {
        Limit* new_root = node->leftChild; // local root

        // attach links above node
        new_root->parent = node->parent;
        if (node->parent == nullptr) {
            this->root = new_root; // set as global root
        } else if (node->parent->leftChild == node) {
            node->parent->leftChild = new_root;
        } else if (node->parent->rightChild == node) {
            node->parent->rightChild = new_root;
        }

        // attach new root's right subtree as left child of old root
        node->leftChild = new_root->rightChild;
        if (node->leftChild != nullptr) {
            node->leftChild->parent = node;
        }

        // make old root right child of new root
        new_root->rightChild = node;
        node->parent = new_root;

    }

} // namespace order_book