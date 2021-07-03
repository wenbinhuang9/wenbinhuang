# Quorum Based Replication Model 
Paritial failures are occuring frequently in distributed system. 

Quorum based replications model is to replicate data on multiple nodes with fault-tolerance of partial failures, like reboot, power off, disk down, network partition. 

## Model 

Quorum based replication uses voting mechanisms. 

Let V be the number of nodes, Vw be the number of nodes accepting the write, Vr be the number of nodes accepting the read. 

It must satisfy two constraints:

1. Vr + Vw > V
2. Vw/2 > V 

The constraint  Vr + Vw > V guarantees that for the most recent writing, the reading can always get the up to date version data. 

The constraint Vw / 2 > V guarantees that  each write must be aware of the most recent write to avoid conflicting writes. 

# Reference 

[Quorum (distributed computing)](https://en.wikipedia.org/wiki/Quorum_%28distributed_computing%29)

Gifford, David K. (1979). Weighted voting for replicated data.

