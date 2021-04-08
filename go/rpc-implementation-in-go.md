# Go: A RPC Example

An RPC example for memory based key value storage.

## RPC Request and Reply Definition

```go
package main

import (
	"fmt"
	"log"
	"net"
	"net/rpc"
	"sync"
)

const {
    OK = "OK"
    ErrNoKey = "ErrNoKey"

}
type Err string 

type PutArgs struct {
    Key string 
    Value string 
}

type PutReply struct {
    Err Err
}

type GetArgs struct {
    Key string
}

type GetReply struct {
    Err Err
    Value string
}

```

## RPC Client Side

```go
func connect() *rpc.Client {
    client, err := rpc.Dial("tcp", ":1234")

    if err != nil {
        log.Fatal("dialing:", err)
    }

    return client 
}

func get(key string) string {
    client := connect()

    args:= GetArgs {"subject"}
    reply := GetReply{}

    err := client.call("KV.Get", &args, &reply)
    if err != nil {
        log.Fatal("error:", err)
    }
    client.close()

    return reply.Value   
}

func put(key string, val string) {
    client := connect()

    args:= PutArgs {"subject", "6.824"}
    reply := PutReply{}

    err := client.call("KV.Put", &args, &reply)
    if err != nil {
        log.Fatal("error:", err)
    }
    client.close()

    return      
}
```

## RPC Server Side

```go

type KV struct {// server side object definition
    mu sync.Mutex
    data map[string]string
}

func server() {
    kv := new(KV)
    kv.data = map[string]string{}

    rpcs := rpc.NewServer()
    rpcs.register(kv)

    l, err := net.Listen("tcp", ":1234")
    if err != nil {
        log.Fatal("listen error", err)
    }
    go func() {
        for {
            conn, err := net.Accept()
            if err == nil {
                go rpcs.ServeConn(conn)
            }else {
                break 
            }
        }
        l.Close()
    }()
}

func (kv *KV) Get(args GetArgs, reply GetReply) error {
    kv.mu.Lock()
    defer kv.mu.UnLock()

    val, ok := kv.data[args.Key]

    if ok {
        reply.Value = val 
        reply.Err = OK
    }else {
        reply.Err = ErrNoKey
        reply.Value  = ""
    }
    return nil
} 


func (kv *KV) Put(args PutArgs, reply PutReply) error {
    kv.mu.Lock()
    defer kv.mu.UnLock()

    kv.data[args.Key] = args.Value
    reply.Err = OK
    return nil
}
```

## main 

```go
func main() {
    server()

    put("suject", "6,824")

    val := get("suject")

    fmt.Println("val is ", val)
}
```