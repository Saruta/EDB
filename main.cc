#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <cstdio>
#include "edb.hh"
#include "config.hh"
#include "elf.hh"

using namespace std;
int status = 0;

void do_child (int argc_, char* argv_[]) {
  ptrace (PTRACE_TRACEME, 0, NULL, NULL); 
  execve (argv_[0], argv_, NULL);
}

void do_trace (pid_t pid_) {
    Edb edb(pid_);
    pid_t w = wait(&status);
    if (w == -1)
      cout << "error" << endl;
    bool ret_ = true;
    while (true) {
      usleep (1000); /* avoid some ugly print */
      std:: string input;
      cout << "(edb) ";
      getline (cin, input);
      if(edb.Parse (input)) 
        ret_ = edb.Execute ();
      if(!ret_)
        edb.error_arg ();
    } 
}

void usage (char* argv[]) {
  cout << "Usage: " << argv[0] << " [PROGRAM]" << endl;
  exit (0);
}

int main (int argc, char* argv[]) {
  if (argc < 2)
    usage (argv); 
  
  ElfReader elfReader (argv[1]); 

  pid_t pid = fork ();

  if (pid == 0) 
    do_child (argc-1, argv+1);
  else
    do_trace (pid);

  return 0;
} 
