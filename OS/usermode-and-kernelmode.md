# User Mode and Kernel Mode

Why currently OS have both user mode and kernel mode? 

Because application may contain malicious code to crash OS. Application may also intentionally break out isolation, for example, an application may interfere other applications by accessing that application's memory. The OS should not trust applications.   So strong isolation is needed between OS and Apps. 

So the OS design should be defensive by dividing OS into two modes kernel mode and user mode. User mode can only execute unpreviliged instructions like sub, add, mov. While only kernel can execute previliged instruction like setting page table, disabling interrupt. 

The user mode get OS services by system call. System call is an API provided by kernel for apps to access OS services. 

### Reference 

[mit 6.S081 introduction](https://pdos.csail.mit.edu/6.S081/2020/schedule.html)



