#ifndef _COMMANDS_H
#define _COMMANDS_H

#include <sys/reg.h>
#include <sys/user.h>
#include <iostream>
#include <iomanip>

class Commands {
  public:
    static void show_arg (const user_regs_struct& regs_);

};

#endif /* _COMMANDS_H */
