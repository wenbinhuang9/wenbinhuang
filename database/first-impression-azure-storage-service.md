# Paper Reading: First Impression on Azure Storage Service 

Takes about 30 minutes to read Azure Storage Service Paper. I will highlight some important details here 

1. A combiniation of bigtable and GFS. Like the file system, the stream layer is a distributed file system with thousands of extent nodes. Each big file is a sequence of extents and each extens is a sequence of blocks. Replication is done within extent nodes by using chaining replication. Like bigtable, partition server is used to managed metadata, transaction and commit log. Partition server is to manage Object Table, Object Table is a kind of mapping from key to value. And the data structure is similar to bigtable, using WAL for commit, using mem store for sequential write. 
2. Global namespace management. Namespace is global, it has a global master to routing the request to different storage stamp. It has hierarchy routing algorithms. The first routing layer is in LS using DNS look up, which means account name is mapping to virtual IP by DNS service. And each vip is pointed to a specific storage stamp. And in FE layer within storage stamp, it caches the mapping of partition name to partition server, and eventually the request is sent to a specifi partition server. 
3. Partition server is serving partion name scalability, data type semantics and also transactions. Partition server mapping the partition name to a specific object, and manages object metadata. 
4. Stream layer is a distributed file system layer. SM is responsible for managing stream namespace, in other words, it maps the stream to a ordered sequence of extents . 
5. Exten node layer is responsible for managing extent and blocks.  Furthe EN traks states of extent replication. 
6. Support multiple data types. It supports Blob, Table and also Queue. Even though data abstraction is different, it uses the same storage and replication infrastructure. 
7. Strong consistency, it provides strong consistency. This is a very interesting topic here

## Some questions 

1. How it provides strong consistency in highly distributed system. 
2. How it manage object tables to acommadate different data abstractions. 
3. What is the concurrency model for transaction. 