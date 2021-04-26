# Microkernel vs Monolithic Kernel

There are two architectures to design kernel, microkernel and monolithic kernel. 

Most OS design uses monolithic kernel like Linux, Ubuntu. 

Before diving into comparisons of two architectures, I will takl about kernel design principles. 

Kernel must be defensive in order not to be crashed. 

So kernel must not trust applications. Becuase application may contain malicious code to crash kernel. 

Further, kernel should not contain bugs becuase application may use bugs to crash kernel. 

As for monolihtic kernel, it includes all features into single kernel, thus increasing kernel complexity, also increasing risks of more bugs. But it takes high performance, because communication and cooperation among kernel components are more easy to deal with. 

As for micro kernel, it includes lesse features as much as possible into kernel, for example, file system implemention is not inside kernel but viewed as a application. As kernel includes less features, so it decreases complexity, leading to less bugs. But it takes extra performance burden, for example, when kernel responses read system call, it has to switch to user mode to  call api provided by file system , and then return back to kernel mode when returning from file system api. 

Summary 

1. Monolithic kernel may take more bugs but high performance
2. Microkernel may take less bugs but low performance. 

