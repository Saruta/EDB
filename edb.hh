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

class Edb {
  public:
    Edb (pid_t pid_);
    bool Parse (const std::string& cmd);
    bool Execute ();
    
  private:
    void _error_arg ();
    pid_t pid;
    std::vector<std::string> tokens;
    std::list<std::string> cmd;
};

#endif /* _EDB_H */
