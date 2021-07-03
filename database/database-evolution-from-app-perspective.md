# Database Architecture Evolution From Application Perspective 

## One Instance 

There is only on instance, read and write requests into the same instance. 

### Pros

1. Simple 

### Cons

1. Single point failure 
2. Not able to hold big data. 

With rapid data increase, a single instance is not able to deal with high throughput and the database performance will become very slow. 

Because the relation database uses B+ tree internally. As for writing request, we can make it sequential write by careful table design,such as using auto increment integer as primary id, so I think writing is not the performance bottlenet

But as query is random, in the worse case, if the index is not carefully designed,  it may scan the whole table. So the read performance decreases with data size increases when you are doing frequently query and also complex query like join.   

### Possible Performance Improvement, Hardwares Upgrade Vertically 

1. Use more memory to reduce disk I/O. 
2. Use quick disk, like solid state disk

## Master and Slave 

In the master salve, it solves the problem of single point failure. Further, it makes read and write seperation possible to improve throughput. 

### Pros 
1. Read and write seperation to improve throughput
2. Avoid single point failure 

### Cons 
1. Read latency. A write has done in master, but still not in slave for reading. 
2. Binlog sync with slave. 

## Sharding 

With data size TB and even bigger and bigger,  the basical idea to deal with big data is sharding. 

### Pros

1. Hold big data, throughput is high 
2. Scale out horizontally, even though still painful. 

### Cons 

1. Increase application design complexity because sharding logic is coupled with application logic. 
2. Scalability is still painful, because the hashing is fixed, you have to migrate data before adding more instances. 
3. Cost is high. On the one hand, we add more instances, on the other hand, the instance may be wasted becuase of low usage. 
4. Distributed transaction occurs because the tables are distributed. 
5. Query may be painful, because a complex query may cross multiple tables. 
6. Golabal transaction ID. The transaction ID has to be global. 

Even though Sharding increases throughput, and also enable painful scalability, the cost is still super high. 

Before diving into next, let's discuss how we can solve the above questions taken by sharding 


### Complex Query Crossing Multiple Sharding Tables

As a logical table is sharded into thousands of tables, it is very difficult and impossible to deal with such complex query crossing table. 

The possible solution is nosql and also the searching system to support big data search like elastic search. 

#### Elastic search

Sync the binlog to elastic cluster, the elastic search will create indexs and to enable search.  And further elastic search is fast.  

### Distributed Transaction

There is a scenario for distributed transaction, A is in table1, B is in table2, A transfer 100$ to B, as table1 and table2 is sharded, so distributed transaction occurs. 

The basical idea for distributed transcation is to use eventual consistency. Strong consitency is the perfect selection, but it takes low performance , which is not acceptable.  

#### Eventual consistency 

There are many mechanisms to ensure eventual consistency.

0. Two Phase Theory, once the first phase is prepared, the system promises the second phase can always be committed. 
1. Retry. Message queue used for repeated try in order to ensure transaction is finished eventually 
2. Logging and Monitoring to find failed transaction. 

But the above implementation is still painful, because the transaction logic is coupled with business logic.  From the application view, the application has to define two pahses, when to rollback, when to commit and when to retry the commit, and the database has to be careful designed to support the status of rollback or commit. 

So it is super and super painful for distributed transaction when using sharding. 

#### Cost is high 

This can be solved by virtualization, use virtual machine to deploy the instance. 

#### Painful Scalability and COW

We need to have a one time migration when scaling out. 

This may be solved by Copy-On-Write when we are in scaling out process. 

#### Increased application design complexity 

Application design complexity always exists, because you have to choose which columns to be used for sharding. 

But we can reduce coding complexity by adding a proxy layer on the top of db sharding clusters to support library and table routing.  

The proxy layer should support routing configuration .

Another solution is to use customized JDBC, JDBC support routing and also routing configuration. 


### Summary of sharding 

Sharding solves the problem of big data. But it takes so many problems too. 

The challenges come from 

1. Carefully select keys for routing
2. Carefully design database table to support distributed transcation. 
3. Carefully coding to support  distributed transcation. 

So sharding is so painful, what is the solution. 


## Proxy Built On the Top Sharding Cluster 

It is a bad practice to make routing logic implemented in application code. 

The basical idea is to adding a proxy layer between sharding cluster and applications . 

The proxy layer is responsible for routing configuration, routing. 

### Pros:

- Migrate routing logic from application to proxy 

### Cons:

- Availability of Proxy Matters
- Add latency. 


## Modify JDBC to support routing 

Another solution is to modify JDBC to support routing . 

### Pros:

- Migrate routing logic from application to JDBC library 

### Cons:

- JDBC is language oriented, for each language , we have to modify JDBC. 


# Summary 
From application perspective, the database evolution is driven by bigger and bigger data size. From single instance to master slave architecture and then to sharding architecture, it solves the problem of supporting big data and high througuput, but it also takes more questions than it solves. 

And with the advent of nosql, we may rethink the internal architecture of relational data storage layer design. One philosophy design of nosql is that database is log, and log is database. All other features is built on the top of log. Consensus algorithm like raft is built on the top of log to implement fault tolerance by log backup. Further, failure recovery can also built on the on of log. 

The combination of nosql and trational relational sql technologies breeds the advent of newsql. 

## Reference 
[How database size affects performance: Theory vs realitys](https://dba.stackexchange.com/questions/22888/how-database-size-affects-performance-theory-vs-reality/22905)


[数据库架构在美团点评的演变实践](https://zhuanlan.zhihu.com/p/31221359)
