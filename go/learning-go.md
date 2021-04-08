
# Learning Go

![](../image/go.png)


## := and =  

These two are all used for assignment statements. 

The following code is to declare a variable s and then assign a string value. 
```go
func hello_world() {
    var s string = "hello world"; 
}
```

But for the convenience, we can use := to replace a var declaration with implicit type.

```go 
func hello_world () {
    s := "hello world"; // declare s to be type string(implicit reasoning) and then assignement 
}
```

So `:=` is a syntax sugar to ease the variable declaration and assignment. 

## range 

range iterates data structure like array, list, map. 

```go
arr := []int{2, 3, 4}

for _, num := range arr {
    fmt.Println(num);
}

kvs:= map[string]string{"hello" : "world"}

for k, v := range kvs {
    fmt.Printf("%s -> %s\n", k, v);
}

```

## defer 
A defer statement deferes the current function execution until the surrounding function returns 

```go

package main 
import (
    "fmt"
)


func main() {
    defer fmt.Println("world")
    fmt.Println("hello")
}

```

## sync 

A library used for multi-threads synchronization like Mutex, WaitGroup

```go
import (
    "sync"
)

var n int = 0 
var mu sync.Mutex
func Inc() {
    mu.Lock()
    n += 1
    mu.Unlock()
}
```

## struct 

Similar to C, Go's struct is useful for organizing data together. 

```go
type person struct {
    name string 
    age int 
}
```

### memory allocation for struct 

```go
p := person {"hello", 13}
```
```go
p := person {}
p.name = "hello"
p.age = 15
```

## make 

make only uses for initialization of slices , maps and channels. 


## go routine 
go routine is a lightweight thread execution. The go routine  syntax ease  multiple-threading programming.  

```go
import (
    "fmt"
)
func worker(i int) {
    fmt.Printf("this is worker %d\n", i)

}

func main() {
    fmt.Println("this is in main")
    for i:= 0; i < 10; i++ {
        go woker(i)
    }
}
```

## Channel 

Channel are pipes for threads communication with interfaces sending values into channel and also receiving from channel

```go
import "fmt"

func main() {
    message := make(chan string) //define a channel
    go func() {
        message <- "ping" // sending a string into channel 

    }()
    msg := <- message // receiving from channel

    fmt.Println(msg)
}

```



## Slice Mem Allocation  

The following program will cause errors
```go 
  arr := []int 
  arr[0] = 1
```




## Reference 

[A Tour of Go](https://tour.golang.org/basics/10)

[Go by Example: Range](https://gobyexample.com/range)