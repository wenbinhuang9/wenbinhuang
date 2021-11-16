# Paper Reading: First Impression in Google Spanner 

Taking 30 minutes to read the paper, take a small notes here.

1. The storage layer is like GFS with single paxos state machine for replication. A set of replicas is composed to a paxos group for replication.  
2. Implement a global order for transaction and concurrency control.  
3. Strong consistency. If it needs cross paxos group coordination, it will use 2PC. 

## Questions 

1. 2PC is expensive, so what is performance for transaction. 
2. How the global time order is implemented, how it is used for concurrency control. 

