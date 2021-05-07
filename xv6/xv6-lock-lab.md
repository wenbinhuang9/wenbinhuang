# xv6: Buffer Cache Lock Lab

The buffer cache uses a global lock `bcache.lock`, it may cause lock contention. 

### Solutions from hints .

> It is OK to use a fixed number of buckets and not resize the hash table dynamically. Use a prime number of buckets (e.g., 13) to reduce the likelihood of hashing conflicts.

it tells us that we need to reorganize the data strucuture, using hash table instead of double linked list.  

- remove double linked list `bcache.head`
- adding a hashtable by simply allocating a static array with prime number, and each bucket in array is a linked list and also maintains a lock. 
- hashtable only stores allocated buffer. getting unused buffer just from `buf array`

> Remove the list of all buffers (bcache.head etc.) and instead time-stamp buffers using the time of their last use (i.e., using ticks in kernel/trap.c). With this change brelse doesn't need to acquire the bcache lock, and bget can select the least-recently used block based on the time-stamps. It is OK to serialize eviction in bget (i.e., the part of bget that selects a buffer to re-use when a lookup misses in the cache).

-  Adding a timestamp to each buffer. where to update timestamp 
-  unused buffer is done by scanning `buf array`, another better solution is using `free list` but also takes complexity.  
- eviction selection is done by scanning `buf array`

> When replacing a block, you might move a struct buf from one bucket to another bucket, because the new block hashes to a different bucket. You might have a tricky case: the new block might hash to the same bucket as the old block. Make sure you avoid deadlock in that case.

    questions: when to replace a block ?