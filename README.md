# order-book
Limit order book in C++ based on the design from this blog: https://web.archive.org/web/20110219163448/http://howtohft.wordpress.com/2011/02/15/how-to-build-a-fast-limit-order-book/

- Each order and limit is stored in a Hashtable for quick access.
- Each limit contains a doubly linked list of orders.
- The book contains two binary search trees of limits - one for Buy and one for Sell.
- Each limit tree is implemented as a self-balancing Red Black Tree, which allows for O(log n) insertion and deletion of limits. If an order already exists in the tree, adding and deleting orders occurs in O(1) time.
- The book provides quick access to the inside of the Book, allowing O(1) execution.

The book is ran using LOBSTER sample order data: https://lobsterdata.com/info/WhatIsLOBSTER.php.  

The project is built using Cmake.  
Each class is unit tested using Catch2.
