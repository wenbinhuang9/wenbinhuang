
# Paper Reading: Aurora Notes

## Design Ideas 

- Log is database
- Move logging off database engine. At the same time , persistence, repliation, recovery is also moved off to shared storage layer. 
- View page data(B+ tree) as cache of log.
- Write is async compared with traditional database 
- Checkpoint is on demand driven by reading. 


## My Questions before Diving into Paper

- What is the difference of aurora from traditional relational database
- Why aurora is faster
- How about scalability in Aurora? 
- Does Aurora support distributed transcation ? 

## What is the difference of aurora from traditional relational database

The engine in traditional relational databse can be divided into two parts, first part is sql processing, and the second part is storage engine. Theses two parts are tightly coupled together in the whole databse engine. 

The aurora move the storage engine part off the database. The storage engine is loosely coupled with sql processing.  And use the ideas from nosql to design a wholely new storage engine. 

Since logging layer is moved off, so replication, recovery and checkpoint can also be moved off. 

## Why aurora is faster

### write redo log async 

- write redo log to storage node, once the redo log is persisted on, it acks back. 
- The rest of replication is done asyncly. 

