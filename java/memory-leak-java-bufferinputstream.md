# Memory Leak From Java BufferInputStream
We have a memory leak found when using BufferInputStream

This is the code 

```java
byte[] contents; 

BufferInputStream buffer = new BufferInputStream(contents.length); 
```

Our application is memory intensive application, we don't want BufferInputStream frequently resizing , which will produce many temporal copy objects to cause frequent GC. 

So, for the above code, we assign the buffer with fixed length. However, it still resizes the buffer. 


Let's take a look at BufferInputStream internal, and found the bug comes from how it resizes the buffer interally.  

The following is a key variable pos in BufferInputStream, this points to the index of next character to be read from the buf array.  
```java 
// The current position in the buffer. This is the index of the next character to be read from the buf array.
protected int pos

```

Let's take a look at the resizing logic 

```java 
pos >= buffer.length // this is the logic to grow buffer 
```

For the above code, the buffer length is  content.length, when we reach the end of content, pos will become content.length. At this time, we met the condition `pos>=buffer.length`, so the buufer is resizing. 

## Debugging Processes And Tools 

1. We use JDK Flight Recorder to dump the memory behaviors.  Add Java Flight Recorder arguments to jvm . 
2. We also use JDK mission control to track which class or method consume much memory, which enable to debug the potential root cause. 
3. And then we use debugging tools like setting break point to follow the BufferInputStream code step by step to identify the behaviors in BufferInputStream. 



   