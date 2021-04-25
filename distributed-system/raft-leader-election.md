# Raft: Leader Election 

### Server States Transfer 

There are three states in raft.

- Leader
- Candidate
- Follower

Follower -> Candidate: when a follower gets time out with leader, it upgrades itself to candidate to compete for leader. 

Candidate -> Follower: when candidate discovers current leader or new term. 

Candidate -> Leader: receives majority of votes 

Leader -> Follower: discover servers with higher term. 


Each server maintains its term, if the current server's term is samller than other server's term, update the term to new. 


