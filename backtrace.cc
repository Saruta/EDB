#include "backtrace.hh"


int 
Bt::backtrace (pid_t pid_)
  {
    unsigned long pc, fp, nextfp;
    int ret, i = 0;
    struct user_regs_struct regs;
    
    ret = ptrace (PTRACE_GETREGS, pid_, NULL, &regs);
    
    if (ret == -1) return -1;

    pc = PROGRAM_COUNTER(regs);
    fp = FRAME_POINTER(regs);

    print_pc(pc,i); 
    while (fp)
      {
        ++i;
        nextfp = ptrace (PTRACE_PEEKDATA, pid_, 
            NEXT_FRAME_POINTER_ADDR(fp),0); 
    
        if (nextfp == (unsigned long) -1) break;

        if (!nextfp) break;
        
        pc = ptrace (PTRACE_PEEKDATA, pid_,
            NEXT_PROGRAM_COUNTER_ADDR(fp),0);

        if (pc == (unsigned long) -1) break;
    
        fp = nextfp;
        print_pc(pc,i); 
      }

    return i;
  }

char **
Bt::backtrace_symbols (pid_t pid) 
  {
    /* TODO */
    return (char**)0;
  }
