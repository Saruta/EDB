#ifndef _BREAKPOINT_H_
#define _BREAKPOINT_H_

#include <iostream>
#include <list>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <unistd.h>

#define BREAK_OPCODE 0xcc

struct breakpoint_t {
  unsigned int addr;
  char* addr_sym;
  unsigned long opcode;
};

class Breakpoint {
  public:
    Breakpoint (pid_t pid);
    bool add (unsigned int addr_);
    bool remove (int index_);
    bool pass_over ();
    void list ();
    bool is_breakpoint ();
  private:
    unsigned int _get_ip ();
    pid_t pid;
    std::list<struct breakpoint_t> bp_tabl;
};


#endif /* _BREAKPOINT_H_ */
