
# Learn GDB 
Let's start from a simple example.

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
