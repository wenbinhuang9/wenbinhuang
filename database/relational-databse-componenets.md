# Relational Database Components 

Here I am going to talk about important components about relational database components. 

## Process Model 
Process model is used to serve multi-user requests.

There are usually 3 process model 

1. Multi threading 
2. Multi process 
3. Thread or process pool

## Parser 

Paser component is to parse the SQL into internal data structure. 

Theoretically, it parses the SQL into algebra expression like projection, filter, hash join, index join, carteson join. 

## Re-Writer 

Re-writer usually serves before query optimizer. 

Re-writer is responsible to re-write SQL statement for performance. 

One example is to rewrite constant expression, for exmaple we can convert 2 + 20 + x to 22 + x 

Another example is to rewrite boolean logic to improve performance by using index join.  For example, 

`Select name  from Employee where not salary > 1000`

We can re-write it to the following statement in order to use salary index .

`Select name from Employee where salary <= 1000`

## Query Optimizer 

For the SQL, it just tells what to do  but not how to do. So how to execute becomes the work of DBMS. 

When the DBMS parses the SQL, theorectially , it converts to algebra expression, as for algebra expression, we can have multiple execution plan.  And we may need to choose a best execution plan for performance consideration. 

The query optimizer is proved to be a NP problem, so we have to use some other heuristic methods to address it, which makes it one of the most complicated componet in relational database. 

It will be very interesting to explore query optimizer algorithms, but I am not deep dive here .

System R gives the initial algorithm for query optimizer, the ideas of which are used by many current commercial database system. 

## Query Plan Executor

When query optimizer is done, it generates query plan. It can generate compiled code, with op code representing different operators. So in this situation, query plan executor plays a role as a interpretor. 

Another solution is to produce a objects tree, each object is a operator, and with input and output, and then composing a tree. And we can execute the tree bottom-up. 

## Transactional Storage Engine 

The current relational database supports transation storage engine. The mysql innodb is one of the most popular transation storage engine. 

When we talk about transaction, we will talk about ACID properties. 

I will give a brief definition of ACID

1. A - Atomicity,  for a transaction , it either all done or does nothing. 
2. C - Consistency, this is a contraint from application perspective,  the data is always consitent before and after a transaction 
3. I - Isolation, the concurrent transactions can not see each other' results. 
4. D - durability, when each transaction is done, it is persisted onto the disk. 


Another important concept for transaction is Serializability. This concept comes from the fact that when we execute transaction sequentially , the result is always correct. But in real world, we want to improve performance, so we execute transactions interleavingly, the reuslt of which is equal to sequential transaction execution, we call it serializability. 

When talking about isolation, we have different isolation levels for trade-off between performance and isolation.


1. Uncommited read,  just read without lock 
2. Commited read, be able to read commited data, lock before read and then release lock immediately after reading. 
3. Repeatable read,  always read the same committed data within a transaction. Lock before read and the release the lock after transaction is done. 
4. Serializability ,  using mechanism like two-phase lock 


   
There are multiple important components behind transaction storage 

1. Lock manager 
2. Buffer manager 
3. Log manager  

Lock provides concurrency control, and also a mechanism to provide isolation, for lock, there are multipe methods. 

1. Two phase lock, lock the read data or write data before transaction, and release it after transaction.  The most popular method for locking in the current commercial database system. 
2. Multi version control lock. This lock is depending on multiple version data with timestamp binded. 
3. Optimistic locking. Each transaction maintain  a copy, when conflict occurs, it rolbacks.


Other commercial system may also provide hierarchy lock. 

Buffer manager is very important for query performance. Usually the relation database is used for online transactions, so  one characteristic of OLTP system is that it operates on small dataset. So for the repeated query page, it can be hit onto cache to reduce I/Os. 

For the buffer manager, the algorithm is the classical LRU algorithm with page replacement policy.  For small data set operations, buffer cache works, but for analytical query, buffer pool is polluted, because page is frequently move in and out the buffer pool, which cause very low performance. So as for analytical query, we may need to have a new strategy algorithm or placement policy. 


For the log manager, it is one of the most complicated system. The log managers ensures the durability. And for the log fluching, it has multiple rules 

1. Log shoud be flushed before pages are flushed
2. Log should be flushed in order
3. Commit log should be flushed to disk before response commit request. 

The first rule  ensures consitency, the second and the third rule are also very important, because it ensures durability. 

As for the log manager, we also need to consider recovery and also checkpoint. we need to ensure recovery is fast and also checkpoint is fast. That's why log manager is complicated, because it has many logic to improve recovery and checkpoint performance. 






