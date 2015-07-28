#include "breakpoint.hh"

using namespace std;

Breakpoint::Breakpoint (pid_t pid_) {
  pid = pid_;
}

unsigned int Breakpoint::_get_ip () {
  return ptrace (PTRACE_PEEKUSER, pid, 4*EIP, NULL);
} 

bool Breakpoint::is_breakpoint () {
  unsigned int ip = _get_ip ();
  std::list<struct breakpoint_t>::iterator it;
  for (it = bp_tabl.begin(); it != bp_tabl.end(); it++)
    if (((unsigned int)it->addr+1) == ip) {return true;}
  return false;
}

bool Breakpoint::add (unsigned int addr_) {
  unsigned long content = ptrace (PTRACE_PEEKTEXT, pid, addr_, NULL);
  struct breakpoint_t bp;
  bp.addr = addr_;
  bp.addr_sym = NULL;
  bp.opcode = content;
  bp_tabl.push_back (bp);

  ptrace (PTRACE_POKETEXT, pid, (unsigned int*)addr_, 
      (unsigned int*) BREAK_OPCODE);
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
  unsigned int ip = _get_ip ();
  std::list<struct breakpoint_t>::iterator it;
  for (it = bp_tabl.begin(); ((unsigned int)it-> addr+1) == ip
      ; it++)
    ;
  ip--;
  it--;
  /* decrement ip */
  ptrace (PTRACE_POKEUSER, pid, 4*EIP, (void*)(ip));
  /* recover opcode at breakpoint */

  ptrace (PTRACE_POKETEXT, pid, it->addr, it->opcode);
  /* single step */
//  for (int i = 0; i< 4; i++)
  ptrace (PTRACE_SINGLESTEP, pid, NULL, NULL);
  usleep (100);
  /* recover breakpoint */
  ptrace (PTRACE_POKETEXT, pid, it->addr, 
      (unsigned int*)BREAK_OPCODE);
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


