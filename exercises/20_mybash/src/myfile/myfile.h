#ifndef __MYFILE_H__
#define __MYFILE_H__

#include "common.h"

#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// ELF 常量 (定义在 elf.h 中，macOS 没有这个头文件)
#define ET_NONE 0
#define ET_REL  1
#define ET_EXEC 2
#define ET_DYN  3
#define ET_CORE 4
#define ELFMAG0 127
#define ELFMAG1 'E'
#define ELFMAG2 'L'
#define ELFMAG3 'F'
#define SELFMAG 4
#define ET_LOOS 0xFE00
#define ET_HIOS 0xFEFF
#define ET_LOPROC 0xFF00
#define ET_HIPROC 0xFFFF

typedef struct {
    unsigned char e_ident[16];
    uint16_t e_type;
} Elf64_Ehdr;

void print_elf_type(uint16_t e_type);

#endif //! __MYFILE_H__
