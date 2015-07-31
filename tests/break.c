#include <stdio.h>

int main() {
  puts (" before breakpoint");
  asm volatile ("int3\n");
  puts (" after breakpoint");
  puts (" Hello ");
  puts (" World! ");
  asm volatile ("int3\n");
  return 0;
}
