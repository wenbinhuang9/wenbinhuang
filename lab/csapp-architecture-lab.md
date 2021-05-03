
# CSAPP Architecture Lab, Part C Optimization 

Part C is a optimization lab. 

Two optimized ideas 

1. Add iaddq to pipeline 
2. Replace subq with iddaq 
3. Use unrolling loop 

Initially, I use four unrolling loop, the code is very similar to the below one. 

And the average CPE I got is `9.86`

```C 
for (int i = 0; i < n - 4; i +=1 ){
    dest[i] = src[i];
    dest[i + 1] = src[i + 1];
    dest[i + 2 ] = src[i + 2];
    dest[i + 3] = src[i + 3];
}
```

Secondly, I increase unrolling length by increasing copying from 4 elements to 8 elements, and got a little improvement of CPE from `9.86` to `9.75`

Thirdly, I found subq can be optimized by using iaddq, then improve from `9.75` to `9.44`

Fourthly, I reorganize the instruction order. 

The original order is like the following code 

```
Loop:	
    mrmovq (%rdi), %r8
    mrmovq (%rdi), %r8
    andq %r8, %r8        
    jle Loop1:             
    iaddq $1, %rax           
Loop1:
    mrmovq (%rdi), %r8
    mrmovq (%rdi), %r8
    andq %r8, %r8          
    jle Loop2:        
    iaddq $1, %rax         
Loop2:
    mrmovq (%rdi), %r8
    mrmovq (%rdi), %r8
    andq %r8, %r8           
    jle Loop3:              
    iaddq $1, %rax      
```

Then I change the instruction order to the below code, increasing performance from `9.44` to `8.66`

```
Loop1:        
        mrmovq (%rdi), %r8
        mrmovq 8(%rdi), %r9
        mrmovq 16(%rdi), %r10
        mrmovq 24(%rdi), %r11
        mrmovq 32(%rdi), %r12
        mrmovq 40(%rdi), %r13
        mrmovq 48(%rdi), %r14
        mrmovq 56(%rdi), %rbx
        rmmovq %r8, (%rsi)
        rmmovq %r9, 8(%rsi)
        rmmovq %r10, 16(%rsi)
        rmmovq %r11, 24(%rsi)
        rmmovq %r12, 32(%rsi)
        rmmovq %r13, 40(%rsi)
        rmmovq %r14, 48(%rsi)
        rmmovq %rbx, 56(%rsi)
ele1:   andq %r8, %r8           # val <= 0?
        jle ele2:               # if so, goto ele1:
        iaddq $1, %rax          # count++, %rax         
ele2:   andq %r9, %r9          
        jle ele3:
        iaddq $1, %rax
ele3:   andq %r10, %r10
        jle ele4:
        iaddq $1, %rax
ele4:   andq %r11, %r11
        jle ele5:
        iaddq $1, %rax
ele5:   andq %r12, %r12
        jle ele6:
        iaddq $1, %rax
ele6:   andq %r13, %r13
        jle ele7:
        iaddq $1, %rax
ele7:   andq %r14, %r14
        jle ele8:
        iaddq $1, %rax
ele8:   andq %rbx, %rbx
        jle Npos1:
        iaddq $1, %rax
```

The score I got is only `8.66`, but the best score is about `7.5`

So the potential optimization direction may be 

1. Use 8th unrolling, then 4th,  and then 2th
2. Keep going to optimize pipeline, such as optimizing Load/use hazard, Processing ret 