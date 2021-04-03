# CSAPP: proxy lab


## Start from simple: implementing a sequential web proxy

### HTTP 1.0

The request is based on http 1.0 and focus on GET method.

A classic get request

```
GET http://www.cmu.edu/hub/index.html HTTP/1.1
```

So we need to parse the http request.

Define data structure of a request 

```C
typedef struct Header {
    char *name;
    char *value;
    struct Header* next;
} Header;

typedef struct Request {
    char method[128];
    char url[128];
    char path[128];
    unsigned int port; 
    char version[128];
    struct Header* headers;
} Request;

```

Define methods 

```C
Request parse_request(char* buf);
```

Sequential Proxy Code Framework (Pseudocode)
```C

// create a listen port 
char* hostname; 
unsigned int listen_port; 
socket listen_fd = open_listenfd(listen_port);

while(1) {  
    sockaddr_in client_addr;
    socket client_socket;
    client_socket = accept(listen_fd, &client_addr, sizeof(sockaddr_in));

    char* buf[1204];

    //read from client socket

    // pass data into http request 
    Request req = parse_request(buf);

    // send request to the server 
    socket proxy_client = open_clientfd(client_socket->ip, client_socket->port);
    sockaddr_in server_addr; 
    socket server_socket = connect(proxy_client, &server_addr, sizeof(sockaddr_in)); 
    
    // read from server
    // write to client.
}

close(listen_fd);

```

## Design Cache for proxy 

### Identify Objects 

Cache Object maintained by double linked list
```C
struct CacheObj{
    char* uri;
    char* object;
    struct CacheObj* prev;
    struct CacheObj* next;
}
```

A cache object

```C
struct Cache{
    int size;
    int capacity;
    struct CacheObj* head; 
    struct CacheObj* rear; // points to last element.
}
```

### Eviction Policy 

The eviction policy is LRU. The cache is maintained by doubly linked list. When cache a object , always inserting into the head, so the object in the front of linked list is always new. When cache is full, evicting the object at rear. 

### Interfaces 

```C
char* read (char* uri); // thread safe

void write(char* uri, char* object); // thread safe 
```

### Helper functions 
```C
void init_cache();
void insert_to_head(struct CacheObj* obj);// thead safe
void remove(struct CacheObj* obj); // thread safe

```



