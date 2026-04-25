#include "myfile.h"

void print_elf_type(uint16_t e_type) {
  const char *type_str;
  switch (e_type) {
  case ET_NONE:
    type_str = "Unknown";
    break;
  case ET_REL:
    type_str = "Relocatable (ET_REL)";
    break;
  case ET_EXEC:
    type_str = "Executable (ET_EXEC)";
    break;
  case ET_DYN:
    type_str = "Shared Object/PIE (ET_DYN)";
    break;
  case ET_CORE:
    type_str = "Unknown";
    break;
  default:
    type_str = "Unknown";
    break;
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int __cmd_myfile(const char *filename) {
  int fd;
  Elf64_Ehdr ehdr;

  fd = open(filename, O_RDONLY);
  if (fd < 0) {
    perror("Failed to open file");
    return 1;
  }

  if (read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr)) {
    perror("Failed to read ELF header");
    close(fd);
    return 1;
  }

  print_elf_type(ehdr.e_type);
  close(fd);
  return 0;
}
