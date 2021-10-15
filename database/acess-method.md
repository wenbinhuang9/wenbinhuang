# Access Method in RDBMS
Access method is another important component in RDBMS (Relational Database Management System). 

There are two major access methods, one is unsorted, another is sorted.

For the unsorted method, we call it heap. While for the sorted method, we call it index. 

The query on the heap may cause full scan, which has a time complexity of O(n). While the index is implemented by B tree, which has a query time complexity of O(logn). 

And current RDBMS also support more complex index like geometry index implemented by R tree and other more complex multi-dimensional index. Postgres implemented multi-dimensional index. 


