# Database Process Model 

Here I am going to talk about relational database process model. 

The commercial relational databse is usally serving multi-users. So we need to have process model to serve request from different users. 

Here I am to talk about three process model used in commercial databases. 

1. Multi Processes  
2. Multi Threads
3. Process Pool or Thread Pool


## Multi Processes Model 

When a customer request comes, the DBMS will create a new process serving that request, when the request is done, that process will be released back to OS. 

The pros is that each process has private address space, there is no shared memory to use, so there will be no bugs from shared memory. 

The cons is that it has a limitation bound to serve more number of requests. 

## Multi Threads Model 

When a customer request comes, the DBMS will create a new thread process serving that request, when the request is done, the thread will be released back to OS.

The pros is that it can scales up to serve more requests compared with multi processes model. 

The cons is that it depends on OS providing thread services, but diferent OS may have different impl of threads, so portability may be a issue.

Another cons is that as threads share memory, if there may be many race condtion issues, and some bugs about memory may cause threads being crashed, the thread isolation is not that good. 

## Threads or Processes Pool Model 

The purpose of pool model is used to avoid frequent creation and deletion of resources to avoid such kind of overhead. 


In commercial databse, mysql uses multi-thread model. And oracle, DB2 and postgres uses multi-process model. 

## Reference 


