#ifndef _EDB_H
#define _EDB_H

#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <signal.h>
#include <unistd.h>
#include "config.hh"
#include "commands.hh"
#include "breakpoint.hh"
#include "backtrace.hh"


class Edb {
  public:
    Edb (pid_t pid_);
    bool Parse (const std::string& cmd);
    bool Execute ();
    void error_arg ();
    ~Edb();
    
  private:
    void _show_arg (const user_regs_struct& regs_);
    
    pid_t pid;
    Breakpoint *bp;
    std::vector<std::string> tokens;
    std::list<std::string> cmd;
};

#endif /* _EDB_H */
