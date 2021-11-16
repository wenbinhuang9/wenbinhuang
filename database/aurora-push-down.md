# Aurora Push Down

Aurora is a new generation database, it reinvents the database architecture, it decouples the storage from the engine. 

For the aurora, the storage service is a distributed system with tens of thousands of nodes. 

One key idea about aurora is that it views log as database. In traditional database, redo log is a recovery mechanism. Further the write is amplified in traditional database, for example, we need to write redo log, bing log, page, double buffer write and also meta data. 

But in aurora, it view redo log as databse, which means , it only writes redo log to storage service, in other words, it pushes the redo log down to storage service. 

So since, rego log is pushed down, we also can push many other things down, for example, backup, restore, recovery, checkpointing. More over, storage service are able to implement many new features like clone, flashback and also parallel query.

Because aurora storage service is a distributed system, so I/O, computation can be distributed to thousands of nodes. And also many pushdown features can be done continuously, asynchrously and distributedly. That's why Aurora is fast. 

