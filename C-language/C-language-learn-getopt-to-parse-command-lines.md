# C: Learn getopt to parse command line arguments

getopt is a library in C used to parse command line arguments. 


Normally, getopt is called in a loop. When getopt returns -1, indicating no more options are present, the loop terminates.

```C
int main(int argc, char *argv[]) {
    while ( optchar = (opgetopt(argc, argv, "hvs:E:")) != -1) {        
    }
    return 0; 
}
```

A switch statement is used to dispatch on the return value from getopt. In typical use, each case just sets a variable that is used later in the program.


```C
int main(int argc, char *argv[]) {
    char c;
    int help; 
    int verbose; 
    int s_flag;
    char* s_value = NULL; 

    while ( c = (getopt(argc, argv, "hvs:")) != -1) {    
        switch(c) {
            case 'h':
                help = 1;
                break;
            case 'v':
                verbose = 1;
                break;

            case 's': // 
                s_flag = 1;
                s_value = optarg;
                break;
            default:
                abort();
        }    
    }
    return 0; 
}
```

Reference:


[Example of Parsing Arguments with getopt](https://www.gnu.org/software/libc/manual/html_node/Example-of-Getopt.html)
