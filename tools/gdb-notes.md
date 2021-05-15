# GDB Notes 

GDB is a tool used for C program debugging 

The following is the C code demo for using gdb. 

```C
#include <stdio.h>

int sum (int a, int b) {
    return a + b;
}
int main() {
    
    int c = sum(10, 20);
    printf("%d\n", c);
 
    return 0;
}
```

`gcc -g sum.c`  to enable debuging. 

`gdb a.out`  to get into gdb. 

`break sum` to set a breakpoint at the entrance of sum.

`run`  to start running the program, it will stops on the breakpoint

`layout split` to show the program also with assemble code. 

`next` to execute next statement, and it will proceed through a function call 

`nexti` to execute next instruction 

`print a` to print variable a

`print $rax` to print value in register %rax

`p *a` to print content in pointer. 

`bt` to print backtrace

`skip` to skip to step into function. 


### Reference 

[csapp gdbnotes](http://csapp.cs.cmu.edu/2e/docs/gdbnotes-x86-64.pdf)