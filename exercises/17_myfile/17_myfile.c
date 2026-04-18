#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// ELF 类型常量 (在 Linux elf.h 中定义)
#define ET_NONE 0
#define ET_REL  1
#define ET_EXEC 2
#define ET_DYN  3
#define ET_CORE 4
#define ELFMAG0 127
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'

typedef struct {
    unsigned char e_ident[16];
    unsigned short e_type;
} Elf64_Ehdr;

void print_elf_type(uint16_t e_type) {
  const char *type_str;
  switch (e_type) {
    case ET_NONE: type_str = "ET_NONE"; break;
    case ET_REL:  type_str = "ET_REL"; break;
    case ET_EXEC: type_str = "ET_EXEC"; break;
    case ET_DYN:  type_str = "ET_DYN"; break;
    case ET_CORE: type_str = "ET_CORE"; break;
    default:      type_str = "ET_UNKNOWN"; break;
  }
  printf("ELF Type: %s (0x%x)\n", type_str, e_type);
}

int main(int argc, char *argv[]) {
  char filepath[2][256] = {
    "./17_myfile.o",
    "./17_myfile",
  };

  int fd;
  Elf64_Ehdr ehdr;

  // TODO: 在这里添加你的代码
  for (int i = 0; i < 2; i++) {
    fd = open(filepath[i], O_RDONLY);
    if (fd < 0) {
      perror("open");
      continue;
    }

    if (read(fd, &ehdr, sizeof(ehdr)) != sizeof(ehdr)) {
      perror("read");
      close(fd);
      continue;
    }

    // 检查 ELF 魔数
    if (ehdr.e_ident[0] != ELFMAG0 || ehdr.e_ident[1] != ELFMAG1 ||
        ehdr.e_ident[2] != ELFMAG2 || ehdr.e_ident[3] != ELFMAG3) {
      printf("%s: Not an ELF file\n", filepath[i]);
      close(fd);
      continue;
    }

    printf("%s:\n", filepath[i]);
    print_elf_type(ehdr.e_type);
    close(fd);
  }
  
  return 0;
}
