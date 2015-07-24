#include "edb.hh"

using namespace std;

Edb::Edb (pid_t pid_) {
  pid = pid_;
  cmd.push_back ("quit");
  cmd.push_back ("kill");
  cmd.push_back ("continue");
  cmd.push_back ("registers");
  cmd.push_back ("u");
  cmd.push_back ("x");
  cmd.push_back ("d");
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
      cmd.end())) {
    tokens.clear ();
        return false;
  }
  
  if (tokens[0] == "quit")
    exit(0);
  else if (tokens[0] == "continue")
    ptrace (PTRACE_CONT, pid, NULL, NULL); 
  else if (tokens[0] == "registers") {
    struct user_regs_struct regs;
    ptrace (PTRACE_GETREGS, pid, NULL, &regs); 
    Commands::show_arg (regs);
  } else if (tokens[0] == "kill")
    ptrace (PTRACE_KILL, pid, NULL, NULL); 
  else if (tokens[0] == "u" || tokens[0] == "x" ||
      tokens[0] == "d") {
    unsigned int count = stoi (tokens[1], nullptr, 10);
    Commands::show_mem (tokens[0][0],count,tokens[2],pid);
  }

  tokens.clear();
  return true;
}

void Edb::error_arg () {
  cerr << "Edb: error arguments " << tokens[0] << endl;
}



