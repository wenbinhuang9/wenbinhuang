
# Use gdb to debug xv6 in Ubuntu

Use following command to start xv6 for gdb debugging 

``` 
make CPUS=1 qemu-gdb
```

Configure .gdbinit
```
echo "add-auto-load-safe-path YOUR_PATH/xv6-labs-2020/.gdbinit " >> ~/.gdbinit
```

Run gdb 

```
gdb-multiarch
```

![](gdb-xv6-debug.png)

