#ifndef _ELF_H_
#define _ELF_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <cstdint>
#include <elf.h>
#include "config.hh"

# define ELF_HEADER_SIZE_64 64
# define ELF_HEADER_SIZE_32 52

# ifdef x86_64
  typedef Elf64_Ehdr Ehdr;
  typedef Elf64_Shdr Shdr;
  typedef Elf64_Sym Sym;
# elif defined i386
  typedef Elf32_Ehdr Ehdr;
  typedef Elf32_Shdr Shdr;
  typedef Elf32_Sym Sym;
# endif

class ElfReader {
  /* this is VERY ugly ^^ */
    std::map<std::string,unsigned int> sym_map;
    std::vector<std::string> section_names;
    std::ifstream elf;
    Ehdr elf_header;
    Shdr shstr_header;
    Shdr sym_header;
    Shdr str_header;
    Shdr test_header;
    void dump_symTable (); 
    void dump_shstrTable (); 
    int extract_section (std::string str, Shdr* shdr);
    void extract_section (unsigned int index_, Shdr* section_);
  public:
    ElfReader (std::string path_);
    unsigned int get_symbol(std::string symb_);
};


#endif /* _ELF_H_ */
