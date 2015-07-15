#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <unistd.h>
#include <cstdio>
#include "edb.hh"

using namespace std;
int status = 0;

void do_child (int argc_, char* argv_[]) {
  ptrace (PTRACE_TRACEME, 0, NULL, NULL); 
  execve (argv_[0], argv_, NULL);
}

void do_trace (pid_t pid_) {
//  while (true) {
    Edb edb(pid_);
    pid_t w = wait(&status);
    if (WIFEXITED(status))
      cout << "exited" << endl;
    if (WIFSIGNALED(status))
      cout << "sig" << endl;
    if (WIFSTOPPED(status))
      cout << "stopped" << endl;
    if (WIFCONTINUED(status))
      cout << "continued" << endl;
 //     break;
    if (w == -1)
      cout << "error" << endl;
      while (true) {
        cout << " (edb) " ;
        std:: string input;
        getline (cin, input);
        if(edb.Parse (input)) 
          edb.Execute ();
      } 
//  }
}

void usage (char* argv[]) {
  cout << "Usage: " << argv[0] << " [PROGRAM]" << endl;
  exit (0);
}

int main (int argc, char* argv[]) {
  if (argc < 2)
    usage (argv); 


  pid_t pid = fork ();

  if (pid == 0) 
    do_child (argc-1, argv+1);
  else
    do_trace (pid);

  return 0;
} 
