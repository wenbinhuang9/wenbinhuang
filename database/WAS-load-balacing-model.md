# WAS load balancing model

Another excellent part in WAS is the load balancing part in the Partition Server Layer. Load balancing is an optimization technique. The load balance logic can be divided into 3 parts. 

1. Range partition placement 
2. Range partition split
3. Range partition merge

When a range partition is created, it needs to deteremine which partition server holds it. Load balance is based on heuristic metrics like disk usage, memory usage, cpu usage and so on. 

Range parition is splitted when a range partition is really very hot.

When range partitions are very cold , it will be merged. 