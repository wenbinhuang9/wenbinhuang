
# Raft and Mathmactical Proof

Proposition 1: Only one peer is elected as leader in each term. 

Proof

```
Prove by contradiction

Assume  peer1 and peer2 are elected as leaders. Let n be the number of peers. Peer1 with m1 > n/2 votes in order to be leader, peer2 with m2 > n/2 votes to be leader too. So total votes is m1 + m2 > n contradicting there are at most n votes. 
```

Proposition 2: If two entries in different logs have the same index and term, then they store the same command. 

Proof 

```
From Proposition 1, we know that only one peer is selected as leader in each term. So if two entries in different logs have the same term, which means two entries are coming from the same leader. Thus, if two entries also have same index and term,  they  store the same command because all two entries replicate a same entry from a same leader. 
```


Proposition 3:  If two entries in different logs have the same index and term, then the logs are identical in all preceding
entries.

Proof 
```
Proof by induction.

Let m denote log index, p1 denote peer 1 and p2 denote p2.

When m = n, two entries with index n in p1 and p2 have the same index and term, then two entries with index n - 1 must have the same index and term because of the fact  the nth entry can be put into p1 or p2's log only when p1 or p2 has the (n-1)th entry with the same index and term with leaders' (n-1)th entry.
```

Proposition 4: A new leader must contain all committed logs of previous leader. 

Proof by contradiction.
``` 
Let p1 be the previous leader, n1, t1 be the previous leaders' last commited entry's index and term. 

Let p2 be the next leader, n2, t2 be the p2's last log index and term before becoming a leader. 

Assume p2 does not contain all committed logs, so we know that p2 does not contain entry with index n1 and term t1, otherwise it contradicts p2 p2 does not contain all commited logs. Thus, n2 < n1 and  t2 <= t1. 

P2 can be elected as leader only when its last log is at least up to date with majority peer's last log. Bug we can prove that majority peer's last log index ni >= n1, because when n1 th entry is commited, it means n1 th entry is sotred in majority of peers. Thus, as n2 < ni , p2's last log index is not at least update to date with majority of peers, contradicting p2 getting majority of votes. 

```
