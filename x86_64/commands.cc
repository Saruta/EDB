#include "../commands.hh"

using namespace std;

void Commands::show_arg (const user_regs_struct& regs_) {
  cout << showbase
        << internal
         << setfill ('0');

  cout << "rax: " << hex << regs_.rax << endl;
  cout << "rbx: " << regs_.rbx << endl;
  cout << "rcx: " << regs_.rcx << endl;
  cout << "rdx: " << regs_.rdx << endl;
  cout << "rsp: " << regs_.rsp << endl;
  cout << "rbp: " << regs_.rbp << endl;
  cout << "rsi: " << regs_.rsi << endl;
  cout << "rdi: " << regs_.rdi << endl;
  cout << "rip: " << regs_.rip << endl;
  cout << "eflags: " << regs_.eflags << endl;
  cout << "cs: " << regs_.cs << endl;
  cout << "ss: " << regs_.ss << endl;
  cout << "ds: " << regs_.ds << endl;
  cout << "es: " << regs_.es << endl;
  cout << "fs: " << regs_.fs << endl;
  cout << "gs: " << regs_.gs << endl;
  cout << "orig_rax: " << regs_.orig_rax << endl;
}

void Commands::show_mem (char type_, unsigned int count_,
    std::string address_, pid_t pid_) {
  unsigned int* p = (unsigned int*)stoi (address_,nullptr,0);
  unsigned int val = 0;
  switch (type_) {
    case 'u':
      cout << dec;
      break;
    case 'x':
      cout << hex;
      break;
    case 'd':
      cout << dec;
    default:
      cout << hex;
  }
  for (int i =0; i < count_; i++) {
    val = ptrace (PTRACE_PEEKTEXT, pid_, p, NULL);
    if (type_ == 'd')
      cout << p << ": " << (int)val << endl;
    else
      cout << p << ": " << val << endl;
    p += 1;
  }
}
