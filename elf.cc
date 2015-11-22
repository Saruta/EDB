#include "elf.hh"

using namespace std;

int ElfReader::extract_section (string str, Shdr* shdr, ifstream& elf) {
  int i ;
  for (i = 0; i< section_names.size(); i++)
    if (str == section_names[i])
      break;
  if (i>= section_names.size ())
    return -1;
  
  int index = i;
  for (int i = 0; i < elf_header.e_shnum ; i++) {
    extract_section (i, shdr, elf);
    if (shdr->sh_name == index)
      break;
  }
  return 0;
}

void ElfReader::extract_section (unsigned int index_, 
				 Shdr* section_, ifstream& elf) {
  elf.seekg (elf_header.e_shoff + index_*sizeof(Shdr));
  elf.read ((char*)section_,sizeof(Shdr));
}


void ElfReader::dump_symTable (ifstream& elf) {
  extract_section (".symtab", &sym_header, elf);
  extract_section (".strtab", &str_header, elf);
  uint32_t symtab_entries = sym_header.sh_size/sym_header.sh_entsize;

  int i;
  char* str_ = new char[40];
  void* str_addr;
  Shdr tmp_sect;
  Sym symbol;
  for (i = 0; i < symtab_entries; i++) {
    elf.seekg (sym_header.sh_offset + sizeof(Sym)*i);
    elf.read ((char*)&symbol, sizeof (Sym));


    if (symbol.st_name != 0) {
      elf.seekg (str_header.sh_offset + symbol.st_name);
      elf.read (str_,40);
    }
    
    if (symbol.st_shndx == SHN_UNDEF) {

      /* do I need to handle this case? */
    } else if (symbol.st_shndx == SHN_ABS) {
      if (symbol.st_name != 0)
        sym_map.insert (pair
          <string,unsigned int>(string(str_),symbol.st_value));
    } else {
      if (symbol.st_name != 0)  
        sym_map.insert (pair
          <string,unsigned int>(string(str_),symbol.st_value));
    } 
  }
  delete str_;

}

void ElfReader::dump_shstrTable (ifstream& elf) {
  extract_section (elf_header.e_shstrndx, &shstr_header, elf);
    char* str = new char[40];
    for (int i = 0; i < shstr_header.sh_size; i++) {
      elf.seekg (shstr_header.sh_offset + i);
      elf.read (str, 40);
      string str_cpp = string (str);
      section_names.push_back (str_cpp);
    }
}


ElfReader::ElfReader (std::string path_) {
  ifstream elf (path_, 
      ifstream::in | ifstream::binary | ifstream::ate);
  if (!elf.is_open()){
    cerr << "Error: unable to open elf" << endl;
    exit(EXIT_FAILURE);
  }
  int elf_size = elf.tellg (); 

  elf.seekg (0, ios::beg);

  vector<uint8_t>::iterator it;
# ifdef x86_64
  elf.read ((char*)&elf_header, ELF_HEADER_SIZE_64);
# elif defined i386
  elf.read ((char*)&elf_header, ELF_HEADER_SIZE_32);
# endif


  dump_shstrTable (elf);
  extract_section (".symtab",&test_header, elf);
  dump_symTable (elf);
  elf.close ();
}

unsigned int ElfReader::get_symbol (std::string symb_) {
  return sym_map [symb_];
}
