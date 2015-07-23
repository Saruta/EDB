#include "commands.hh"

using namespace std;

void Commands::show_arg (const user_regs_struct& regs_) {
  cout << showbase
        << internal
         << setfill ('0');

  cout << "eax: " << hex << regs_.eax << endl;
  cout << "ebx: " << regs_.ebx << endl;
  cout << "ecx: " << regs_.ecx << endl;
  cout << "edx: " << regs_.edx << endl;
  cout << "esp: " << regs_.esp << endl;
  cout << "ebp: " << regs_.ebp << endl;
  cout << "esi: " << regs_.esi << endl;
  cout << "edi: " << regs_.edi << endl;
  cout << "eip: " << regs_.eip << endl;
  cout << "eflags: " << regs_.eflags << endl;
  cout << "cs: " << regs_.xcs << endl;
  cout << "ss: " << regs_.xss << endl;
  cout << "ds: " << regs_.xds << endl;
  cout << "es: " << regs_.xes << endl;
  cout << "fs: " << regs_.xfs << endl;
  cout << "gs: " << regs_.xgs << endl;
  cout << "orig_eax: " << regs_.orig_eax << endl;
}
