# xv6: First Milestone 

Congratulations to myself, I have already finished all mit 6s.081 lab. All labs are very great, and are very helpful for me to dive into getting know what is a real OS. 

My favorite labs are all relating to page fault exception, including Lazy-Allocation, Copy-On-Write and mem-map, which demonstrates that current OS benefits much from virtual memory. 

Locking lab is very interesting, it provides an opportunity to improve the parallelism by changing the data structure. 

Thread switching  helps to understand the key concept of context switching and it also helps to understand some important registers such as return address register, program counter register.

System calls help to understand how to implement a system call, and when the process is getting into kernel space, things become different, the process may not be able use its pagetable, so the system call arguments have to copy from user space into kernel space. 

Trap lab is very great, it provides a opportunity to optimize the `copyin`, it mereges the kernel page table and user page table into one, so when user process gets into kernel space, the address translation in `copyin` can be done by hardwares rather than software to significantly improve performance. 

File system lab helps to understand how to implement a file system. Actually, the implementation of file system in xv6 is very elegant and the layer of file system is so clear. And the implementation of file system including many great techniques like `cache` and  `crach recovery by logging`. 


Further, xv6 is a very smalle kernel, compiling is also very fast, it is really a great kernel to read the code line by line before diving into Unix OS. And we can also have many ideas to optimize xv6, such as adding slab allocator to support frequent data structure allocation and deallocation, and also buddy system  to reduce internal fragmentation. 


Anyway, mit6s081 is one of the greatest course I have ever learned. 

The next, I will finish code reading of xv6, and also compare with Linux kernel. 
