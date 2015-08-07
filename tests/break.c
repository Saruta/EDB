#include <stdio.h>

void func1 ();

int main() {
  puts (" before breakpoint");
  asm volatile ("int3\n");
  puts (" after breakpoint");
  puts (" Hello ");
  puts (" World! ");
  asm volatile ("int3\n");
  return 0;
}

void func1 () {
  puts ("This is func1");
}
