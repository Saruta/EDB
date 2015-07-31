#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/user.h>
#include <iostream>
#include <iomanip>
#include <string>

#define DEC  "d"
#define HEX   "x"
#define UDEC  "u"

class Commands {
  public:
    static void show_arg (const user_regs_struct& regs_);
    static void show_mem (char type_, unsigned int count_,
        std::string address_, pid_t pid_);
    static long get_ip (pid_t);
    static void set_ip (pid_t, long);
    static void decrement_ip (pid_t);
};

#endif /* _COMMANDS_H */
