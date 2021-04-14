# Raft: Leader Election 

### Server States Transfer 

There are three states in raft.

- Leader
- Candidate
- Follower


Follower -> Candidate: when follower gets time out with leader, it upgrades itself to candidate to compete for leader. 

Candidate -> Follower: when 

