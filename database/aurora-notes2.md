# Paper Reading: Aurora Notes 2

The paper name is : Amazon Aurora: Design Considerations for High
Throughput Cloud-Native Relational Databases

## The Goal 

Obviously, just like the name in paper, the goal is high throughput.

## What is the contraints for high throughput 
The paper says it is network. So the goal is transfered to reduce network traffic. 

## Architectures to Support the Goal
- Decouple of storage and computnig.Redo log is loaded off into a multi-tenant scale-out storage service enabling fault toerance and self-healing across multiple data-centers. 
- 

## Questions 

- What is  durability at cloud scale, and what is  quorum system? 
- What is double-write technique in MYSQL 
- What is mini-transaction in MYSQL 