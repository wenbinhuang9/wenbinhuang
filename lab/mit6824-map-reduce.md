# mit6.824: map reduce lab 

## Design

### Coordinator 

Coordinator plays a role in scheduling tasks and managing workers

#### Data Structure 

```go
type Coordinator struct {
	// Your definitions here.
    mu sync.Mutex
    maptasks []task
    reducetasks []task 
}

const (
    IDLE = 0
    INPROCESS = 1
    COMPLETED = 2
)
type task struct {
    taskID int 
    tasktype int
    status  int 
    url string 
    wokerID int 
}
```

#### RPC interface 

```go
type RequestTaskArgs struct {
    WorkerID int 
}

type RequestTaskReply struct {
    TaskType int 
    TaskID int 
    Urls []string 
    Err string
}

type DoneTaskArgs struct {
    TaskType int 
    TaskID int 
    WorkerID int 
    TmpFileName string 
}
type DoneTaskReply struct {
    Err string
}
func (c *Coordinator) RequestTask(args RequestTaskArgs, reply RequestTaskReply) error

func (c *Coordinator) DoneTask(args DoneTaskArgs, reply DoneTaskReply) error 
```

#### Heper Functions 

```go
task findIdleTask(); 

```

### Worker

1. 

### Communication 




