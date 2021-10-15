# RDBMS architecture 

Previously, the RDBMS are not parallel architecture, it is an uniprocessor architecture. But with the development multi-processors architecture, we need to consider the architecture of RDBMS. 

## Shared Memory 

This is usually a single machine with multi-processors, each processor has multiple CPUs. And each processor is to share the memory. For this architecture, if the data volume increases, we have to scale up vertically, but it is impossible to scale up infinitely. 

So we have another architecture shared nothing. 

## Shared Nothing 

Shared nothing is a distributed system with a collection of cheap , commercial machines. Each processor has its local memory and also disk, so nothing is shared. Based on this architecture, we should carefully partition the data. And each machine contains only part of data. From the application layer, it has to deal with many issues, like distributed transaction, distributed deadlock detection, which adds much complexity to application development. And application layer has to deal with partial machine failure. 

## Shared Disk 

One drawbacks of shared nothing architecture is that the application layer has to partion data carefully. And as the data is partitioned, it takes high complexity to deal with distributed transaction etc. 

Shared disk is to address this issue. For the shared disk architecture, multipe processes share the disk. Shared disk architecture is enabled by Storage Area Network, which uses a collection of machines to serve as a large virtual volume for sharing. 

One classical shared disk architecuture is Amazon Aurora. The disk is shared for all DB instances. And it allows many features pushed down to shared disk layer, like backup, recovery etc. 
