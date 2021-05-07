# xv6: multithreading lab 

### Implementation Goals and Questions

> Goal 1 :  One goal is ensure that when thread_schedule() runs a given thread for the first time, the thread executes the function passed to thread_create(), on its own stack.

Goal 1 Impl Questions  

1. When, where and how to run the thread function. 
    - When the thread is scheduled for the first time. So the function should be triggered in thread_sched. The function is not directly exectued, we only  need to change pc. 
    - pc points to the next intruction to execute, so we may need to initialize pc and also load and resotre pc during context switch.  
    - Instead, swtch saves the ra register,
which holds the return address from which swtch was called.  From here , we know that we need to let `ra store pc`.
2. How to run the thread function on its stack. 
    - use `sp` register 


> Goal 2:  Another goal is to ensure that thread_switch saves the registers of the thread being switched away from, restores the registers of the thread being switched to, and returns to the point in the latter thread's instructions where it last left off.

Goal 2 Impl Questions 
1. As we store register into thread strucuture, how to pass arguments into thread_switch, and how thread_switch retrieves arguments 
   - retrieves arguments from registers, a0, a1 is used as arguments to callee conventionally. 


### Impl Details 
Adding a context switch , same as context structure in `proc.h`
```C 
// Saved registers for kernel context switches.
struct context {
  uint64 ra;
  uint64 sp;

  // callee-saved
  uint64 s0;
  uint64 s1;
  uint64 s2;
  uint64 s3;
  uint64 s4;
  uint64 s5;
  uint64 s6;
  uint64 s7;
  uint64 s8;
  uint64 s9;
  uint64 s10;
  uint64 s11;
};

struct thread {
  char       stack[STACK_SIZE]; /* the thread's stack */
  int        state;             /* FREE, RUNNING, RUNNABLE */
  struct context    c; 

};
```

`t->c.ra = (uint64)func; ` returns back to pc. 
`t->c.sp` runs on the thread stack 
```C
void 
thread_create(void (*func)())
{
  struct thread *t;

  for (t = all_thread; t < all_thread + MAX_THREAD; t++) {
    if (t->state == FREE) break;
  }
  t->state = RUNNABLE;
  // YOUR CODE HERE
  t->c.ra = (uint64)func; 
  t->c.sp = (uint64)(t->stack + STACK_SIZE); // stack grows down
}
```

`thread_switch((uint64)&t->c, (uint64)&next_thread->c);`, context switch here. 
```C
void thread_schedule(void)
{
  struct thread *t, *next_thread;

  /* Find another runnable thread. */
  next_thread = 0;
  t = current_thread + 1;
  for(int i = 0; i < MAX_THREAD; i++){
    if(t >= all_thread + MAX_THREAD)
      t = all_thread;
    if(t->state == RUNNABLE) {
      next_thread = t;
      break;
    }
    t = t + 1;
  }

  if (next_thread == 0) {
    printf("thread_schedule: no runnable threads\n");
    exit(-1);
  }

  if (current_thread != next_thread) {         /* switch threads?  */
    next_thread->state = RUNNING;
    t = current_thread;
    current_thread = next_thread;
    /* YOUR CODE HERE
     * Invoke thread_switch to switch from t to next_thread:
     * thread_switch(??, ??);
     */
    thread_switch((uint64)&t->c, (uint64)&next_thread->c);

  } else
    next_thread = 0;
}

```

Switch is done by assembly code. a0 is the first argument, a1 is the second argu.
```C
	.text

	/*
         * save the old thread's registers,
         * restore the new thread's registers.
         */

	.globl thread_switch
thread_switch:
	/* YOUR CODE HERE */
		sd ra, 0(a0)
        sd sp, 8(a0)
        sd s0, 16(a0)
        sd s1, 24(a0)
        sd s2, 32(a0)
        sd s3, 40(a0)
        sd s4, 48(a0)
        sd s5, 56(a0)
        sd s6, 64(a0)
        sd s7, 72(a0)
        sd s8, 80(a0)
        sd s9, 88(a0)
        sd s10, 96(a0)
        sd s11, 104(a0)

        ld ra, 0(a1)
        ld sp, 8(a1)
        ld s0, 16(a1)
        ld s1, 24(a1)
        ld s2, 32(a1)
        ld s3, 40(a1)
        ld s4, 48(a1)
        ld s5, 56(a1)
        ld s6, 64(a1)
        ld s7, 72(a1)
        ld s8, 80(a1)
        ld s9, 88(a1)
        ld s10, 96(a1)
        ld s11, 104(a1)
        
		ret    /* return to ra */

```


