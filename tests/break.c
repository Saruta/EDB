#include <stdio.h>

int little_elf = 0;

void func1 ();

int main() {
  puts (" before breakpoint");
  puts (" after breakpoint");
  puts (" Hello ");
  func1 ();
  puts (" World! ");
  asm ("int3");
  return 0;
}

void func1 () {
  puts ("This is func1");
}
