# WAS Replication Model

Replication is a very foundamental topic in storage system for durability, availability and disaster recovery. 

In WAS, it uses chain replication to ensure both the consistency and availability. 

The most challenging part in chain replication is that how it handles the failures. In WAS, it handles the chain replication failures elegantly and smartly.  When there is a write failure, it will automatically seal the extent, in other words, the sealed extent can not be written again. And for the new writes, it will assign a new extent. This greatly eases the failure model in chain replication. Here, the failure is detected by the write behavior, if write fails , it assuems there is a failure in some node of the chain. 

