#include "edb.hh"

using namespace std;

Edb::Edb (pid_t pid_) {
  pid = pid_;
  cmd.push_back ("quit");
  cmd.push_back ("kill");
  cmd.push_back ("continue");
  cmd.push_back ("registers");
}

bool Edb::Parse (const string& cmd) {
  string last_item = "";
  if (cmd == "")
    return false;

  /* split the string */
  
  for (int i = 0; i< cmd.length(); i++) {
    if (cmd[i] == ' ') {
      tokens.push_back (last_item);
      last_item = "";
    } else if (i == (cmd.length() -1)) {
      tokens.push_back (last_item + cmd[i]); 
    }else {
      last_item += cmd[i];
    }
  }

  /* erase empty tokens */

  int i,j;
  int old_size = tokens.size();
  for (i = 0, j = 0; i< old_size ; i++) {
    if (tokens[j] == "") {
      tokens.erase (tokens.begin() + j); 
    } else {
      j++;
    }
  }

  if (tokens.size() == 0)
    return false;
  return true;
}

bool Edb::Execute () {
  if ((tokens.size() < 1) ||
      (std::find(cmd.begin(), cmd.end(), tokens[0]) ==
      cmd.end()))
        return false;
  
  if (tokens[0] == "quit")
    exit(0);
  else if (tokens[0] == "continue")
    ptrace (PTRACE_CONT, pid, NULL, NULL); 
  else if (tokens[0] == "registers") {
    struct user_regs_struct regs;
    ptrace (PTRACE_GETREGS, pid, NULL, &regs); 
    cout << "rax: " << regs.rax << endl;
    cout << "rbx: " << regs.rbx << endl;
    cout << "rcx: " << regs.rcx << endl;
  } else if (tokens[0] == "kill")
    ptrace (PTRACE_KILL, pid, NULL, NULL); 

  tokens.clear();
  return true;
}

void Edb::_error_arg () {
  cerr << "Edb: error arguments" << endl;
}




