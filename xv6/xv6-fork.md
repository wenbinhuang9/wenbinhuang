# xv6: fork 

fork is a system call to create a  child process. The impl of fork can be divided into below stages

- Allocate a  process  data structure `struct proc`.
- Copy parent mem into child mem
- Reference file descriptors from parent. 


`allocproc()` is to allocate a `proc struct`. 

`uvmcopy` is to copy mem from parent to child. 

`*(np->trapframe) = *(p->trapframe);` is to copy the parent's saved registers into child's saved registers. trapframe is a physical page used to save and restore registers when trap occurs and then forces current process to switch to kernel space. 

`np->trapframe->a0 = 0;`  when using fork, we have the code like below.

```C
pid = fork();
if (pid==0) {
  //exec child's process
}
else if (pid > 0) {
  //exec parent's process
}else {
  // fork fails
}
```

The return value of fork() is stored in a0 register, and of course the child process of fork() is returned back to 0. So np->trapframe->a0 is set to 0, when child swtiches back to user space, a0 will be restore into 0.  

`np->ofile[i] = filedup(p->ofile[i]);` is to reference file descriptors, which means the parent and child share same file descriptors. 
```C
// Create a new process, copying the parent.
// Sets up child kernel stack to return as if from fork() system call.
int
fork(void)
{
  int i, pid;
  struct proc *np;
  struct proc *p = myproc();

  // Allocate process.
  if((np = allocproc()) == 0){
    return -1;
  }

  // Copy user memory from parent to child.
  if(uvmcopy(p->pagetable, np->pagetable, p->sz) < 0){
    freeproc(np);
    release(&np->lock);
    return -1;
  }
  np->sz = p->sz;

  np->parent = p;

  // copy saved user registers.
  *(np->trapframe) = *(p->trapframe);

  // Cause fork to return 0 in the child.
  np->trapframe->a0 = 0;

  // increment reference counts on open file descriptors.
  for(i = 0; i < NOFILE; i++)
    if(p->ofile[i])
      np->ofile[i] = filedup(p->ofile[i]);
  np->cwd = idup(p->cwd);

  safestrcpy(np->name, p->name, sizeof(p->name));

  pid = np->pid;

  np->state = RUNNABLE;

  release(&np->lock);

  return pid;
}
```

`proc[NPROC]` is a global array storing 64 `proc` structures, which means xv6 supports at most 64 processes. From here, we know that xv6 uses the most simple way, using static array, to manage allocation of process data structure.   In real world, like unix , it uses `double linked list` to maintina all processes and then uses `slab allocator`  to allocate and deallocate process data structure. 

`proc_pagetable(p)` is to allocate a empty page table for process. 


```C
// Look in the process table for an UNUSED proc.
// If found, initialize state required to run in the kernel,
// and return with p->lock held.
// If there are no free procs, or a memory allocation fails, return 0.
static struct proc*
allocproc(void)
{
  struct proc *p;
  // 1. Allocating a proc structure from `proc[NPROC]`
  for(p = proc; p < &proc[NPROC]; p++) {
    acquire(&p->lock);
    if(p->state == UNUSED) {
      goto found;
    } else {
      release(&p->lock);
    }
  }
  return 0;

found:
  p->pid = allocpid();

  // Allocate a trapframe page.
  if((p->trapframe = (struct trapframe *)kalloc()) == 0){
    release(&p->lock);
    return 0;
  }

  // An empty user page table.
  p->pagetable = proc_pagetable(p);
  if(p->pagetable == 0){
    freeproc(p);
    release(&p->lock);
    return 0;
  }

  // Set up new context to start executing at forkret,
  // which returns to user space.
  memset(&p->context, 0, sizeof(p->context));
  p->context.ra = (uint64)forkret;
  p->context.sp = p->kstack + PGSIZE;

  return p;
}
```

### Pros and Cons 

Pros 

- simplicity. `proc` is maintained by a static array to make allocate a process data structure to be extremely easy. 

Cons 

- Copy mem from parent to child is most time consuming of fork. The solution to solve this is to implement a copy on write. 
- Only 64 processes are allow in maximum. This can be solved by dynamically allocate and deallocte `proc` using ideas like `object poos`, `slab allocator`
- Each process is assigned a page for `trapframe`. `trapframe` is only used for hundreds of bytes, causing `internal framentation`, linux solves this by using `slab allocator`. 
  
### Linux World 

- Uses `double linked list` to dynamically link all processes. 
- Uses `slab allocator` to allocate and deallocate processes with flexibility. `slab allocator` also helps reduce internal framentation. 
- Memory is copy on write, this is one of the most successful optimization of fork in linux. 



