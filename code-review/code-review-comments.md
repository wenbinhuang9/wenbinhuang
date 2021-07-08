# Code Review and Comments 

There are some principles to when and how to write comments. 

## Write Less Comments and Make Code Self Expressive
The first principle is that we should code comments as less as possible. 

On the one hand, if the code itself is expressive enough, we don't need to write any redundant comments. On the other hand, if the code is not expressive, one way is to try to make it expressive. 

The code below is a redundant comment. 
```C
i++; // increment
```

The code below is not expressive , so it needs comment 

```Java
// Check to see if the employee is eligible for full benefits
if( (employee.flags & HOURLY_FLAG) && employee.age > 65) {

}
```

But the above code can be transfered into expressive code as  following 

```Java
if( employee.isElgibleForFullBenefits()) {

}
```

## Make Comment Consistent with Code

Code tells the truth, however, comments may lie with time going. The situation is that when the code is updated but the comment is not updated to be outdated, which may mislead the developer and even propagate false knowledge. 

So when the code is updated, be careful about the surrounding comments, make it consistent with the code too. 


## Reference 

Clean Code
