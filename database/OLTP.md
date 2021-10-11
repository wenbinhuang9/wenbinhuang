# OLTP 

OLTP is a online transaction processing system. 

The exmaple of OLTP system like online order, payment, banking system. Especially, financial system use OLTP frequently in their daily transactions.  

This kind of systems require low latency, high throughput, so it has a critical requirement for performance.

Another important property is that it usually deals with small sets of data for each transaction. 

The realational database is created to support OLTP. 

The core concept in OLTP system is transaction, transaction makes OLTP possible. 

I will give an example here to explain how transaction supports OLTP. 

Consider a scenario, A is transfer 100$ to B. This can be done by two steps. 

1. Decrease 100$ in A's account 
2. Increase 100$ in B's account 

In order to make this transaction succeeds, 4 conditions must be met. 

1. Atocimity. We want 2 steps all succeed, or 2 steps all fail. It is not acceptable that we decrease 100$ in A's , but not increase 100$ in B's 
2. Durability. After transaction succeeds, we want to make the transaction durable. It is not acceptable that when transaction succeeds, the data is persisted. 
3. Concurency. The balance's in both A and B are consistent after transaction succeeds. 
4. Isolation. Before transaction succeeds, other transactions are not able to observe the data of unfinished transation. For example, if A's account is decreased, but transaction still not finished, other transactions are not able to see this change. 

So these four properties are required for a transaction, which will be supported by relational database. 
