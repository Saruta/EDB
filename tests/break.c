#include <stdio.h>

int main() {
  puts (" before breakpoint");
  asm volatile ("int3\n");
  puts (" after breakpoint");
  return 0;
}
