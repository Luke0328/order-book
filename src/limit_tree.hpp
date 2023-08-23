#ifndef LIMIT_TREE_H
#define LIMIT_TREE_H

namespace order_book {

    class Limit;

    class LimitTree {
        private:
            Limit* root;

            void LeftRotate(Limit* node);
            void RightRotate(Limit* node);

        public: 
            LimitTree();

            void Insert(Limit* limit);
            void Delete(Limit* limit);

            ~LimitTree();

    };

} // namespace order_book

#endif 
