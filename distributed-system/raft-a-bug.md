# Raft: A Bug

## Conlfict Log Truncate Error
When implementing raft in mit 6824 lab, there is a bug with information below.
```
--- FAIL: TestFigure8Unreliable2C (204.37s)

apply error: commit index=10 server=1 3329 != server=2 6414
```

The log is in inconsistency. 

So the way to debug is to print each peer's commited log. 

Just like the below log, initially, command 6414 has been inserted into peer 1
```
[peer 1, term 6] 2021/05/16 04:15:28 AppendEntries Success {1 0} [0xc00000cdc0 0xc00000cde0 0xc00000ce00 0xc00000ce20 0xc00000ce40] 0xc000067d80 1 0 6 2 [{0 <nil> 0} {2 9481 1} {2 8950 2} {2 2272 3} {2 697 4} {2 2696 5} {4 7529 6} {4 5018 7} {6 6661 8} {6 3680 9} {6 6414 10}] 1 1 map[1:1] 8 0 [0 0 0 0 0] [0 0 0 0 0] 1621138528569 0xc00001a420}

```

But it is overriden by the command 3329. So it seems the log is truncated. 
```
[peer 1, term 13] 2021/05/16 04:15:30 Start args 3329
[peer 1, term 13] 2021/05/16 04:15:30 Start reply 10, 13, true | [{0 <nil> 0} {2 9481 1} {2 8950 2} {2 2272 3} {2 697 4} {2 2696 5} {4 7529 6} {4 5018 7} {6 6661 8} {6 3680 9} {13 3329 10}]
```

Let's look at the code causing the truncation 

I directly truncate the log in the statement `rf.log = rf.log[0 : (args.PrevLogIndex + 1)]` , this is incorrect because it may also truncate the good log. The truncation occurs only when the entry conflicts occur. 

```go
	if len(args.Entries) > 0 {
		rf.log = rf.log[0 : (args.PrevLogIndex + 1)]

		
		rf.log = append(rf.log, args.Entries...)
		rf.persist()	
	}
```
This is the correct code to truncate  the conflict entry.

```go 
	for _, e := range args.Entries {
		if e.Index < len(rf.log) && e.Term == rf.log[e.Index].Term{
			// do nothing
			Assert(e.Index == rf.log[e.Index].Index, "AppendEntries") 
		}else if e.Index < len(rf.log) && e.Term != rf.log[e.Index].Term {
			//If an existing entry conflicts with a new one (same index
			//but different terms), delete the existing entry and all that
			//follow it
			rf.log = rf.log[0:e.Index]
			rf.log = append(rf.log, e)
			rf.persist()

			Assert(e.Index == rf.log[e.Index].Index, "AppendEntries") 
		}else {
			// Append any new entries not already in the log
			rf.log = append(rf.log, e)
			rf.persist()
		}
	}
```

## Time Out and Livelock Error 

TestFigure8Unreliable2C is easily to fail because of livelock causing time out. 

So be careful to check guidance here [student's guide to raft](https://thesquareplanet.com/blog/students-guide-to-raft/#an-aside-on-optimizations)

In `student's guide to raft`, it provides some tips to solve live lock. And check your code carefully 

>  a) you get an AppendEntries RPC from the current leader (i.e., if the term in the AppendEntries arguments is outdated, you should not reset your timer); 
> 
> b) you are starting an election;
> 
>  or c) you grant a vote to another peer.

## Incorrect Use of Lock 

The following code has a bug, that is when the peer becomes follower, it can still append entries with new updated term. The error occurs because ` args := rf.makeAppendEntriesArgs(peer)` is not locked, and when executing this statement , the peer may not be a leader causing to append entries with latest term.  

```go 
func (rf *Raft) sendAppendEntriesAsync(peer int) {	

	go func() {
		rf.mu.Lock()

		if rf.role != LEADER {
			PrefixDPrintf(rf, "not a leader, stop to send AppendEntries")
			rf.mu.Unlock()
			return
		}
		
		rf.mu.Unlock()
        args := rf.makeAppendEntriesArgs(peer)
        		
		var reply AppendEntriesReply

		ok := rf.sendAppendEntries(peer, &args, &reply)

		rf.sendAppendEntriesCallback(ok , peer, args, reply)
	}() 
}
```

The correct code should be 


```go
func (rf *Raft) sendAppendEntriesAsync(peer int) {	
	go func() {
		rf.mu.Lock()

		if rf.role != LEADER {
			PrefixDPrintf(rf, "not a leader, stop to send AppendEntries")
			rf.mu.Unlock()
			return
		}
        args := rf.makeAppendEntriesArgs(peer)
		rf.mu.Unlock()
 		
		var reply AppendEntriesReply
		ok := rf.sendAppendEntries(peer, &args, &reply)
		rf.sendAppendEntriesCallback(ok , peer, args, reply)
	}() 
}
```
