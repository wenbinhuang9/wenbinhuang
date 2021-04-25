# mit6824: Debug Raft Leader Election 

Initially my first version implementation of Raft leader election uses synchronous ways. 

That is when starting a leader election, a candidate sends RequestVote to other peers synchronously, just like the code as following 

```go
for peer range rf.peers {
    sendRequestVote(peer, args, reply)
}
```

When I use this method, I can rarely pass  the test case `election after network failure` and `multiple elections`, but I can always pass the test case ` initial election`

I guess the problem may lie in `requesting votes in sync way`. For example, there are 7 peers and  the election time out is 300ms, each requesting vote takes 50 ms, so requesting votes taking 300ms leads to timeout. 

So the solution is using async RequestVote to other peers.

```go
	for server := 0; server < n; server += 1 {
		if server != rf.me {
			// todo make it concurrent here 
			args := RequestVoteArgs {rf.currentTerm, rf.candidateId, -1, -1}
			var  reply  RequestVoteReply
			rf.sendRequestVoteAsync(server, args, reply) // any return value here 
		}
    } 
```

sendRequestVoteAsync details as following 
```go
func (rf *Raft) sendRequestVoteAsync(server int, args RequestVoteArgs, reply RequestVoteReply) {
	go func(){
		ok := rf.sendRequestVote(server, &args, &reply)
		rf.sendRequestVoteCallBack(ok, server, args, reply )
	}()

}
```

The key lies in call back funciton as following 

```go 
func (rf *Raft) sendRequestVoteCallBack(ok bool, server int, args RequestVoteArgs, reply RequestVoteReply) {
	if ok == false {
		PrefixDPrintf(rf, "sendRequestVote to peer %d fails\n", server)
		return 
	}
	rf.mu.Lock()
	defer rf.mu.Unlock()

	if(rf.role != CANDIDATE) {
		return
	}
	
	if reply.Term > rf.currentTerm {
		// stop election 
		PrefixDPrintf(rf, "stops election because of smaller currenterm = %d, reply term =%d, reply server = %d\n", rf.currentTerm, reply.Term, server)
		rf.role = FOLLOWER
		rf.currentTerm = reply.Term
		rf.votedFor = NILVOTE
		rf.voteCount = make(map[int]int)
		 
	} else if rf.role == CANDIDATE && reply.VoteGranted == true && reply.Term == rf.currentTerm  {
		PrefixDPrintf(rf, "got voted from server %d\n", server)
		rf.voteCount[server] = 1
		DPrintf("server %d get vote nums= %d\n", rf.me, len(rf.voteCount))
	}	

	if (len(rf.voteCount) > len(rf.peers) / 2 && rf.role == CANDIDATE) {
		rf.role = LEADER
		DPrintf("congratulations server %d  term %d becomes leader, got votes %d\n", rf.me, rf.currentTerm, len(rf.voteCount))
		n := len(rf.peers)
		//send initial empty AppendEntries RPCs (heartbeat) to each server in async
		for server := 0; server < n; server += 1{
			if (server != rf.me) {
				go rf.sendOneHeartbeat(server)
			}
		}
	}
}
```
