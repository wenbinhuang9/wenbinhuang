# Clean Code and Functions 
## Small Functions 
We should make functions small enough to make it readable and also maintainable. 

If a function is composed of hundreds lines of code, it will be messy and increase complexity to read the code. And such a function should be refactored to make it small .

Generally, a function  either should not cross the whole screen or be smaller than 50 lines. 

## Do One Thing, Do It Well

This is a single responsibility principle. This is also a philosophy of Unix Programming. 

There is an example in Unix World. Unix provides many simple tools to interact with OS. These tools respect single responsibility principle.

For example, as for file management and access tools, Unix divides it into many small commandlines. 

1. `cd` for changing directory 
2. `ls` for list files in a directory 
3. `rm` for remove a file
4. `touch` for creating a file. 

Unix implenments file management using many small tools rather than putting all those functions into a big bucket.

## No Side Effects 

Side effects in a function may cause bugs, and make the function be tricky. 

The code following has side effects. From the method name, `checkPwd` should not have side effect, it just checks password. But here, it changes the data of Session.

```Java

public boolean checkPwd(String name, String pwd) {
    User user = UserGateway.findByName(name);
    if( user != NULL) {
        if (user.verifyPwd(pwd) == True) {
            Session.init();
            return true; 
        }
    }
    return false; 
}
```

The correct way to do it should be like the following code.

```Java


public boolean checkPwd(String name, String pwd) {
    User user = UserGateway.findByName(name);
    if( user != NULL) {
        return user.verifyPwd(pwd);
         
    }
    return false; 
}

public void static main() {
    if (checkPwd(name, pwd) == true) {
        Session.init();
    }
}
```

## Less Arguments 

The best thing for a function is to have no arguments, then 1 argument and then 2 arguments. 

If there are more than 3 arguments, the cost to use that function will be increased.  Because the more arguments, the more complex inner the function, and the more you need to understand how the function works.  So if there are more than 3 arguments, please consider if you need to refactor that function. 

## Rerence 

Clean Code 