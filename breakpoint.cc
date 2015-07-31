#include "breakpoint.hh"

using namespace std;

Breakpoint::Breakpoint (pid_t pid_) {
  pid = pid_;
}

bool Breakpoint::is_breakpoint () {
  long ip = Commands::get_ip (pid);
  std::list<struct breakpoint_t>::iterator it;
  for (it = bp_tabl.begin(); it != bp_tabl.end(); it++)
    if (((long)it->addr+1) == ip) {return true;}
  return false;
}

void Breakpoint::_decrement_ip () {
  long val = Commands::get_ip (pid);
  Commands::set_ip (pid, val-1);
}

bool Breakpoint::add (unsigned int addr_) {
  unsigned long content = ptrace (PTRACE_PEEKTEXT, pid, addr_, NULL);
  struct breakpoint_t bp;
  bp.addr = addr_;
  bp.addr_sym = NULL;
  bp.opcode = content;
  bp_tabl.push_back (bp);

  ptrace (PTRACE_POKETEXT, pid, (unsigned int*)addr_, 
      (char) BREAK_OPCODE);
  return true;
}

bool Breakpoint::remove (int index_) {
  std::list<struct breakpoint_t>::iterator it;
  it = bp_tabl.begin ();
  advance (it, index_);
  ptrace (PTRACE_POKETEXT, pid, it->addr, it->opcode);
  bp_tabl.erase (it);
  return true;
}

bool Breakpoint::pass_over () {
  unsigned int ip = Commands::get_ip (pid);
  std::list<struct breakpoint_t>::iterator it;
  for (it = bp_tabl.begin(); ((unsigned int)it-> addr+1) == ip
      ; it++)
    ;
  it--;
  /* decrement ip */
  _decrement_ip ();
  /* recover opcode at breakpoint */

  ptrace (PTRACE_POKETEXT, pid, it->addr, it->opcode);
  /* single step */
  ptrace (PTRACE_SINGLESTEP, pid, NULL, NULL);

  usleep (400);
  /* recover breakpoint */
#ifndef x86_64 // FIXME 
  ptrace (PTRACE_POKETEXT, pid, (unsigned int *)it->addr, 
      (char)BREAK_OPCODE);
#endif
  usleep (400);
  return true;
}

void Breakpoint::list () {
  std::list<struct breakpoint_t>::iterator it;
  cout << "index ||  address  || symbol" << endl;
  cout << "----------------------------" << endl;
  for (it = bp_tabl.begin(); it != bp_tabl.end(); it++)
    cout << "  " << std::distance(bp_tabl.begin(),it)+1
      << "   ||  " << hex << it-> addr << "  || " << 
      ((it->addr_sym==NULL)?"   _":it->addr_sym) << endl;
} 


