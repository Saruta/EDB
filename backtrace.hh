/*
 * Inspired from pstack
 */

#ifndef _BACKTRACE_H_
#define _BACKTRACE_H_

#include <iostream>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <sys/reg.h>
#include "config.hh"

# ifdef x86_64
#   define FRAME_POINTER(regs) (regs.rbp)
#   define PROGRAM_COUNTER(regs) (regs.rip)
# elif defined i386
#   define FRAME_POINTER(regs) (regs.ebp)
#   define PROGRAM_COUNTER(regs) (regs.eip)
# endif

# define NEXT_FRAME_POINTER_ADDR(fp) (fp)
# define NEXT_PROGRAM_COUNTER_ADDR(fp) (fp + __SIZEOF_POINTER__)
# define print_pc(pc,i) (std::cout << std::dec << " ("<< i <<  ") "\
      << std::hex << "0x" << pc << std::endl)

namespace Bt 
  {

    extern int backtrace (pid_t pid);

    extern char **backtrace_symbols (pid_t pid);
  }

#endif /* _BACKTRACE_H_ */
