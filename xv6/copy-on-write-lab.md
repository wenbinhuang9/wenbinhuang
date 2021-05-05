# mit 6s081: copy on write lab 

### Implementation Ideas and Details 

1. COW fork() creates just a pagetable for the child, with PTEs for user memory pointing to the parent's physical pages. COW fork() marks all the user PTEs in both parent and child as not writable.
   - Modify uvmcopy() to map the parent's physical pages into the child, instead of allocating new pages.
   -  Clear PTE_W in the PTEs of both child and parent. 

2. When either process tries to write one of these COW pages, the CPU will force a page fault. The kernel page-fault handler detects this case, allocates a page of physical memory for the faulting process, copies the original page into the new page, and modifies the relevant PTE in the faulting process to refer to the new page, this time with the PTE marked writeable.
   - Modify usertrap() to recognize page faults. It may be useful to have a way to record, for each PTE, whether it is a COW mapping. You can use the RSW (reserved for software) bits in the RISC-V PTE for this.
   - When a page-fault occurs on a COW page, allocate a new page with kalloc(). And if there's no free memory, the process should be killed.
   - copy the old page to the new page
   - and install the new page in the PTE with PTE_W set

3. COW fork() makes freeing of the physical pages that implement user memory a little trickier. A given physical page may be referred to by multiple processes' page tables, and should be freed only when the last reference disappears.
   - A good way to do this is to keep, for each physical page, a "reference count" of the number of user page tables that refer to that page. 
   - It's OK to to keep these counts in a fixed-size array of integers. Using array, get index by pa/PAGESIZE, array length, and give the array a number of elements equal to highest physical address of any page placed on the free list by kinit() in kalloc.c.
   - Set a page's reference count to one when kalloc() allocates it.
   - Increment a page's reference count when fork causes a child to share the page
   - and decrement a page's count each time any process drops the page from its page table
   - kfree() should only place a page back on the free list if its reference count is zero

4. Modify copyout() to use the same scheme as page faults when it encounters a COW page.
