
# Go: A Web Crawler Implementation

## Serial Crawler 

Let's implement a simple serial crawler first. 

```go
package main

import (
	"fmt"
	"sync"
)

func Serial (url string, fetcher Fetcher, fetched map[string]bool) {
    if (fetched[url]) {
        return 
    }
    fetched[url] = true
    urls, err := fetcher.Fetch(url)
    if err != nil {
        return 
    }

    for _, u := range urls {
        Serial(u, fetcher, fetched)
    }
    return 
}

```

## Concurrent crawler 

Crawling is time consuming, so let's optimize the serial crawler by leveraging concurrency. 

One of chanllenges of multi-threading program is that we need to be careful about shared states, so we need to use sync tools to protect shared data. 



```go
type fetchState struct {
    mu sync.Mutex
    fetched map[string]bool
}

func ConcurrentMutex(url string, fetcher Fetcher, f *fetchState) {
    f.mu.Lock()
    already := f.fetched[url] 
    f.fetched[url] = true
    f.mu.Unlock()

    if(already) {
        return 
    }
    urls, err := Fetcher(url)
    if (err != nil) {
        return 
    }
    var done sync.WaitGroup
    for _, u := range urls {
        done.Add(1)

        go func(u string ) {
            defer done.Done()
            ConcurrentMutex(u, fetcher, f ) 
        }(u)
    }
    done.Wait()
    return 
}

func makeState() *fetchState {
    f = &fetchState{}
    f.fetched = make(map[string]bool)
    return f
} 
```

## Concurrent Crawler with Channel

It is a coordinator, worker model. 

1. Worker's job is to fetch urls, and then send urls back to coordinator by channel.
2. Coordinator receives urls from channel and if url is not visited, marked it visited and then assign a new job to a worker. 
```go

func woker(url string, ch chan []string, fetcher Fetcher) {
    urls, err := Fetcher.Fetch(url)
    if (err != nil ) {
        ch <- []string{} // send empty urls
    } else {
        ch <- urls
    }
}

func coordinator(ch chan []string, fetcher Fetcher) {
    fetched := make(map[string]bool)
    n := 1
    for urls := range ch { // blocked until 
        for _, url := range urls {
            if (fetched[url]== false) {
                fetched[url] = true
                n += 1
                go worker( url, ch fetcher)
            }
        }
        n -= 1
        if (n == 0) {
            break // no message to receive, exit 
        }
    }

}

func ConcurrentChannel(url string , fetcher Fetcher) {
    ch := make (chan []string)

    go func() {
        ch <- [] string{url} 
    }()

   coordinator(ch, fetcher) 
}

```


