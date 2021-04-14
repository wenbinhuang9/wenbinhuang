# Unix Fork

To prove parent's memory not being shared after forking child process, I write the following code to demonstrate it. 

```C
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    char* s = "hello world";
    int arr[] = {1, 2,3};
    pid_t c = fork();

    if(c == 0) {
        printf("pid %d, %s\n", getpid(), s);

        for (int i = 0; i < 3; i ++) {
            arr[i] = 6 - arr[i];
            printf("%d ", arr[i]);
        }
        printf("\n");
    }else {
        sleep(3);
        printf("pid %d, %s\n", getpid(), s);

        for (int i = 0; i < 3; i ++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    }

    exit(0);
}
```
The output is 

```
pid 80970, hello world
5 4 3 
pid 80969, hello world
1 2 3 
```

From the output, arr is modified by child, but arr in parent is still unchanged. 

So , we can know that 

1. Child process does not share memory with parent process, each has its own address space. 
2. When forking, the memory in parent is copied to child. 
