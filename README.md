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

```
#!shell
(edb) continue # at breakpoint run the program
(edb) next [count] # single step * count, if no count, count = 1
(edb) break 0xCAFE # breakpoint at 0xCAFE
(edb) blist # list breakpoint
(edb) bdel [index] # delete a breakpoint (index is display with blist)
(edb) [x/u/d] [count] 0xCAFE # memory dump at 0xCAFE (size = count*4 bytes)
# x -> hexa, u -> unsigned, d -> signed int
(edb) kill # kill the process
(edb) quit # exit debugger
(edb) registers # show registers

```


another way to add a breakpoint, put an int3 


```
#!c
asm volatile ("int3 \n"); // breakpoint
```