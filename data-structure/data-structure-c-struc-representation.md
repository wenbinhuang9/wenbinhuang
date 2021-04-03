
# Data Structure: C struct representation

## Linear Structure 

### Linkedin List 

```C
struct Linkedlist{
    int data;
    struct Linkedlist* next;
}
```

### Double Linkedin List

```C
struct Dlinkedlist{
    int data;
    struct Dlinkedlist* next;
    struct Dlinkedlist* prev; 
}
```

### Stack 

```C
struct Stack{
    int* data;
    int capacity;
    int top;
}
```

### Queue

```C
struct Queue {
    int* data;
    int capacity;
    int size;
    int front;
    int rear;
}
```

## Trees 

### General Trees

```C
struct Tree{
    int data;
    struct Tree** child_list;
}
```

### Binary Tree 

```C
struct Bintree{
    int data;
    Bintree* left;
    Bintree* right;
}
```

## Graph 

### Adjacent Matrix

```C
struct Adjmatrix{
    int* data;
    int vertex_size;
}
```
### Adjacent List

```C
struct node* {
    int vertex;
    struct node* next;
}

struct Adjlist{
    int vertex_size;

    node** head;
}
```
