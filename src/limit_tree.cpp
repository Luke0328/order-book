#include <iostream>
#include <stack>
#include <string>

#include "limit.hpp"
#include "limit_tree.hpp"

namespace order_book {

    LimitTree::LimitTree()
    {
        this->root = nullptr;
        this->TNIL = new order_book::Limit();
        this->TNIL->color = BLACK;
    }

    void LimitTree::LeftRotate(Limit* node)
    {
        // std::cout << "Left Rotate" << std::endl;
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
        if (new_root->leftChild != this->TNIL) {
            node->rightChild->parent = node;
        }

        // make old root left child of new root
        new_root->leftChild = node;
        node->parent = new_root;
    }

    void LimitTree::RightRotate(Limit* node) {
        // std::cout << "Right Rotate" << std::endl;
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
        if (node->leftChild != this->TNIL) {
            node->leftChild->parent = node;
        }

        // make old root right child of new root
        new_root->rightChild = node;
        node->parent = new_root;

    }

    bool LimitTree::IsLeftChild(Limit* node) 
    {
        return node->parent->leftChild == node;
    }

    void LimitTree::FixInsert(Limit* node) 
    {
        // std::cout << "FixInsert" << std::endl;
        // Case 1: node is root
        if (node == this->root) {
            // std::cout << "Case 1" << std::endl;
            node->color = BLACK;
            return;
        }

        while (node->parent->color == RED) {
            Limit* uncle;
            if (IsLeftChild(node->parent)) {
                uncle = node->parent->parent->rightChild;
                if (uncle->color == RED) {
                    // Case 2: uncle is red - recolor
                    // std::cout << "Case 2" << std::endl;
                    node->parent->parent->color = RED;
                    uncle->color = BLACK;
                    node->parent->color = BLACK;
                    node = node->parent->parent;
                } else {
                    // Case 3: uncle is black - triangle
                    if (!IsLeftChild(node)) { 
                        // std::cout << "Case 3" << std::endl;
                        node = node->parent;
                        this->LeftRotate(node);
                    }
                    // Case 4: uncle is black - line
                    // std::cout << "Case 4" << std::endl;
                    node->parent->parent->color = RED; 
                    node->parent->color = BLACK;
                    this->RightRotate(node->parent->parent);
                }
            } else {
                uncle = node->parent->parent->leftChild;
                if (uncle->color == RED) {
                    // Case 2: uncle is red - recolor
                    // std::cout << "Case 2:2" << std::endl;
                    node->parent->parent->color = RED;
                    uncle->color = BLACK;
                    node->parent->color = BLACK;
                    node = node->parent->parent;
                } else {
                    // Case 3: uncle is black - triangle
                    if (IsLeftChild(node)) {
                        // std::cout << "Case 3:2" << std::endl;
                        node = node->parent;
                        this->RightRotate(node);
                    }
                    // Case 4: uncle is black - line
                    // std::cout << "Case 4:2" << std::endl;
                    node->parent->parent->color = RED;
                    node->parent->color = BLACK;
                    this->LeftRotate(node->parent->parent);
                }
            }
            if (node == this->root) {
                break;
            }
        }
        this->root->color = BLACK;
    }

    Limit* LimitTree::Insert(Limit *limit) 
    {
        Limit* curr = this->root;
        Limit* prev = nullptr;
        while (curr && curr != this->TNIL) {
            prev = curr;
            if (limit->limitPrice <= curr->limitPrice) {
                curr = curr->leftChild;
            } else {
                curr = curr->rightChild;
            }
        }
        limit->parent = prev;
        if (prev == nullptr) {
            this->root = limit;
        } else if (limit->limitPrice <= prev->limitPrice) {
            prev->leftChild = limit;
        } else {
            prev->rightChild = limit;
        }

        limit->leftChild = this->TNIL;
        limit->rightChild = this->TNIL;
        limit->color = RED;

        // std::cout << "Insert" << std::endl;
        Limit* original = limit;
        this->FixInsert(limit);
        return original;
    }

    void LimitTree::RevOrderPrint() 
    {
        std::stack<Limit*> st;

        Limit* curr = this->root;
        while ((curr && curr != this->TNIL) || !st.empty()) {
            while (curr && curr != this->TNIL) {
                st.push(curr);
                curr = curr->rightChild;
            }

            curr = st.top();
            st.pop();
            std::string line = 
                "Price: " + std::to_string(curr->limitPrice) + " - " + 
                "Size: " + std::to_string(curr->size) + " - " + 
                "Volume: " + std::to_string(curr->totalVolume);
            std::cout << line << std::endl;

            curr = curr->leftChild;
        }
    }

    void LimitTree::Print() 
    {
        this->RevOrderPrint();
    }

    Limit* LimitTree::GetRoot()
    {
        return this->root;
    }

    Limit* LimitTree::GetTNil()
    {
        return this->TNIL;
    }

    void LimitTree::DestroyRecursive(Limit *node)
    {
        if (node && node != this->TNIL) {
            DestroyRecursive(node->leftChild);
            DestroyRecursive(node->rightChild);
            delete node;
        }
    }

    LimitTree::~LimitTree() 
    {
        DestroyRecursive(this->root);
        delete this->TNIL;
    }

} // namespace order_book