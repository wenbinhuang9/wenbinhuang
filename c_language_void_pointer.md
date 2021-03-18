# C: void pointer

## Advantages
One advantages of void pointer is that it can points to any types of data. 

```C 

char var_char = 'A';
int var_int = 83;

void* void_p;
void_p = &var_char;
printf("var_char is %c", *(char *)void_p);

void_p = &var_int;
printf("var_int is %d", *(int *)void_p);
```

## Disavantages

### Not Support Direct Dereferencing 

When we compile the following code, we will get the compiler error because the compiler don't know which data type to represent. 
```C
char var_char = 'A';
void* void_p = &var_char;

printf("var_char is %c", *void_p);
```

So the solution is using `type casting`

```C
printf("var_char is %c", *(char * )void_p);
```

## Applications

1. Used in `malloc` to support allocate memory for any types of data.
2. Used in `generic data structure` implementation, such as generic linked list.  
