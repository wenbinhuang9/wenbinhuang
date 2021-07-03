# Quorum Model in Aurora

For the details about quorum model for serverless replication, check [wikipedia: Quorum (distributed computing)](https://en.wikipedia.org/wiki/Quorum_%28distributed_computing%29) or the paper  `Gifford, David K. (1979). Weighted voting for replicated data`

The current distributed replication system usually chooses 3 replicas. But in Aurora, it chooses 6 replicas with 2 replicas in each 3 AZs(Availability Zone). The 6 replicas consumes more network bandwidth, why aurora make such a decision. 

Consider a failure scenario, there are only 3 replicas distributed in AZ A, B, C.  And C fails because of a fire, and then B also has concurrently rebooting failure, which will cause only 1/3 replica available. However, only 1 replica response is not able to read most recent writes. 

In order to avoid the above two concurrent failures, aurora uses 6 replicas with 2 replicas in each  3 AZs.  Aurora uses 4/6 for writing and 3/6 for reading. So as for reading, it allows one AZ failure(fire, flood etc.) and one replica background noise failure in another AZ( rebooting, disk corruption, netwok etc.) concurrently, which is called AZ + 1 failures in Aurora paper. As for writing, it allows one AZ failure. 

So when AZ + 1 occurs, reading is still in available. Further, Ensure read quorum  enables to rebuild write quorum by adding additional replica copies. 

### The assumption in the quorum model deisign

- 1. The ZA + 1 Failure is possible, but the propability should be very small.
- 2. The three concurrent failures is extremely small. 

### Summary of key points 

1. The 6 replicas with 2 replicas in 3 AZs make Aurora tolerant with concurrent AZ + 1 failures. 
2. Tolerance of concurrent AZ + 1 failures does not break read quorum, which enable the repairment of write quorum. 

### New Questions Taken from Quorum Model 

- It will increase Network IOs, which may sacrafice performance. 

# Reference 

Amazon Aurora: Design Considerations for High Throughput Cloud-Native Relational Databases


