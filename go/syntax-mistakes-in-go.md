# Mistakes I Make When Programming Golang 


Declare variable in the following way. Yes , go syntax is a little different. 

```go
int a
```

Forget to use `exported name` in RPC struct definition.
```go 
type RequestVoteReply struct {
	term int
	voteGranted bool
}
```

Modify struct data in a wrong way as following. The correct way to modify struct data is to use pointer as parameters. 
```go
type RequestVoteReply struct {
	Term int
	VoteGranted bool
}

func modifyReply (reply RequestVoteReply) bool {
    reply.VoteGranted = false 
}
```

Use map wihtout memory allocation 
```go 
m := map[int]bool 
```

Iterate 0 to n using range 
```go
n := 10 
for i := range n {

}
```



