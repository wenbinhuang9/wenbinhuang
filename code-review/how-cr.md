# How to Code Review

As for code review, I think the the most important parts are readability and correctness. 
## Readability 

1. Is the code readable, understandable and self explainable at glance. If not, it is too complicated. 
2. If comment is added, are the comments understandable and also adding values to the code. 

## Correctness 

1. Is there major issues ?
2. Is the code in full test, how about the test coverage? Is the test case testing the new feature? 


## Backward Compatibility

1. If there is a change relating to APIs, is that backward compatible? 
2. If it is not backward compatible? What should be done ? 


## Dependency 
1. Is there new dependency? 
2. Is new dependency necessary and required ? 
3. Is new dependence risky? Any operations work we need to do for the new dependency ? 

And there are more topics we can discuss about code review such as failure handling, design change, operation work, code duplication and reuse, performance, configuration and security. I will dive into these topics in future. 

