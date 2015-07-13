#include <iostream>
#include <cstdlib>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ptrace.h>
#include <unistd.h>

using namespace std;

void do_child (int argc_, char* argv_[]) {
  ptrace (PTRACE_TRACEME, 0, NULL, NULL); 
  execve (argv_[0], argv_, NULL);
}

void do_trace () {


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
    do_trace ();

  return 0;
} 
