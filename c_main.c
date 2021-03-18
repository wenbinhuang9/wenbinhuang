#include<stdio.h>
int main()
{
    int arr_int[3] = {100, 200,300};
    
    void* p_void = (void* ) arr_int;

    void* p_void_incr = p_void + 1;

    printf("p_void address is %u, p_void_incr address is %u\n", p_void, p_void_incr);
    printf("p_void value is %d, p_void_incr value is %d", *(int*)p_void, *(int*)p_void_incr);

    return 0;
}