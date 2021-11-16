# Storage System Durability 

Durability is an important feature when designing a large scale storage system. 

The decouple of computing and storage has been a popular design in modern storage system. It is untorable that the data is corrupted because of hardware failures, disaster etc. So durability is a very important feature in modern storage system. 

The basic mechanism of durability is replication. 

GFS gives a solution for durability, that each chunk is to be replicated 3 times. 

And Windows Azure Storage also privodes durability by using chain replication. 

The durability in Aurora is interesting, it is a leaderless design, and each data is replicated 6 times in 3 Available Zones, and this design is combined with Quorum Model for fault toerance. 

So when designing a scalable distributed system, we should consider how to design the durability. 
