# xv6: Debug Locking Lab

When optimizing xv6 cache buffer lock contention, the most time I spent is on debugging. There are two reasons of bug.

1. Pointer is error-prone, and I still not get familiar with pointer.
2. Operations on linked list is also error prone, because operations like inserting, deleting is error-prone. 

### Pointer Bug

There is a bug below. I want to delete a buf node in doubly linked list. The bug is here `struct buf b = table[i]; `, which will cause the deletion is computed on `&b` but not `&table[i]`, because `&b != &table[i]` at this time. So the deletion fails below.  
```C
struct buf {
  int valid;   // has data been read from disk?
  int disk;    // does disk "own" buf?
  uint dev;
  uint blockno;
  struct sleeplock lock;
  uint refcnt;
  struct buf *prev; // LRU cache list
  struct buf *next;
  uchar data[BSIZE];
  uint ts; 
};

struct buf table[NBUCKET];// each element in table is a doubly linked list with a dummy head. 

static void
rm(int blockno, struct buf *e) // remove buf in double linked list 
{
    e->prev->next = e->next;
    e->next->prev = e->prev;

    e->next = (struct buf*)0;
    e->prev = (struct buf*)0;
}

// here is bug exist
struct buf b = table[i]; 
rm(&b);
```

The way to fix above bug is to make `rm` directly on `table[i]`, which is `rm(&table[i])`. 

### Doubly Linked List  Operation Bug

Another bug is in the `rm` operation, which is to delete a node in doubly linked list.  The bug is here `e->prev = e->next;`, it should be `e->prev->next = e->next;`

```C
static void
rm(int blockno, struct buf *e) // remove buf in double linked list 
{   
    
    e->prev = e->next; // bug is here
    e->next->prev = e->prev;

    e->next = (struct buf*)0;
    e->prev = (struct buf*)0;
}
```



