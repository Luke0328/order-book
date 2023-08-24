#ifndef LIMIT_TREE_H
#define LIMIT_TREE_H

#include "limit.hpp"

namespace order_book {

    class Limit;

    class LimitTree {
        private:
            Limit* root;
            Limit* TNIL;

            void LeftRotate(Limit* node);
            void RightRotate(Limit* node);
            bool IsLeftChild(Limit* node);
            void FixInsert(Limit* node);

            void RevOrderPrint();

        public: 
            LimitTree();

            Limit* Insert(Limit* limit);
            void Delete(Limit* limit);

            Limit* GetRoot();
            Limit* GetTNil();

            void Print();

            void DestroyRecursive(Limit* node);
            ~LimitTree();

    };

} // namespace order_book

#endif 
