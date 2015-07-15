#include <stdio.h>

int main() {
  puts (" before breakpoint\n");
  asm volatile ("int3\n");
  puts (" after breakpoint\n");
  return 0;
}
