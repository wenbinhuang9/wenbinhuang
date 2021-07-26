# Java: why we need factory design pattern 

When creating objects in Java, we usually encourage to create a factory to produce an object. Why we use factory design pattern to produce an object ? 

Let's consider the situation that we don't use factory to manage objects.

## Example 
The scenario is that we have a payment interface. 

```Java

public interface Pay {
    ReturnCode pay(User payer, User payee);
}
```

Initially, we have a version 1 implementation of Pay interface 

```Java
public class PayImplV1 {
    ReturnCode pay(User payer, User payee) {
        System.out.println("The first version implementation of pay interface");

        return ReturnCode.SUCCESS; 
    }
}
```

And we have three classes to use pay interface. 

```Java

public class A {
    private class Pay pay;
    public A(){
        pay = new PayImplV1(); 
    }
}

public class B {
    private class Pay pay;
    public B(){
        pay = new PayImplV1(); 
    }
}

public class C {
    private class Pay pay;
    public C(){
        pay = new PayImplV1(); 
    }
}
```

Right now, we need to support a new version of payment API, we called a version 2 

```Java
public class PayImplV2 {
    ReturnCode pay(User payer, User payee) {
        System.out.println("The second version implementation of pay interface");

        return ReturnCode.SUCCESS; 
    }
}
```

In order to use PayImplV2 API, we have to modify code in class A, B and C. This is kind of modfication is very painful. If the PayImplV1 is used in hundreds of class, it is more painful to modify it. To solve this issue, we can use factory design pattern. 

```Java
public class A {
    private class Pay pay;
    public A(){
        pay = new PayImplV2(); 
    }
}

public class B {
    private class Pay pay;
    public B(){
        pay = new PayImplV2(); 
    }
}

public class C {
    private class Pay pay;
    public C(){
        pay = new PayImplV2(); 
    }
}
```

## Solution: Using Factory 

We define a factory class as following 
```Java
public class PayFactory {
   
    public static getInstance() {
        return new PayImplV1();
    }
}
```
We are to create Pay object in class A, B, C using PayFactory 

```Java
public class A {
    private class Pay pay;
    public A(){
        pay = PayFactory.getInstance(); 
    }
}

public class B {
    private class Pay pay;
    public B(){
        pay = PayFactory.getInstance(); 
    }
}

public class C {
    private class Pay pay;
    public C(){
        pay = PayFactory.getInstance(); 
    }
}

```

When we want to make A, B, C to use PayImplV2. We only need to change the code in PayFactory. 

```Java
public class PayFactory {
    public static getInstance() {
        return new PayImplV2();
    }
}
```

## Benefits of Using Factory Pattern 

1. Factory offers a centralized place to create objects, which benefits future interface upgration. 
2. Factory patterns encourages interface oriented programming. Factory pattern let user to focus on the user of interface rather than creation. 


## Spring: Solve the Issue of Frequently Defining Trivial Factory 

Since it is encouraged to use factory pattern, so for a specific interface, we need to create a corresponding factory, which is trivial.  If we have thousands of interfaces,  we may need to create thousands of factories too. So Spring is created to solve this issue. 

Spring framework is to manage creation, injection and binding of objects, wih Spring framework, we don't need to write hundreds of factory, we just let spring container to deal with that.

## Guice: Another Light-Weight Injection Framework

Compared with Spring, Spring is a huge monster. However, Guice provides a very light weight injected framework ! 








