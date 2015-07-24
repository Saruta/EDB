### EDB ###
/!\ always in development

Easy DebuGer is a micro version of 
gdb-like tool for easy debug.

### How do I get set up? ###


```
#!shell
./configure arch=i386  # x86_64 no implemented yet
make 
./edb [prog] # no arguments implemented yet

```



### Features ###

* continue # at breakpoint run the program
* kill # kill the process
* quit # exit debugger
* registers # show registers
to add a breakpoint, put an int3 


```
#!c
asm volatile ("int3 \n"); // breakpoint
```