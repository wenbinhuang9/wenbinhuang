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