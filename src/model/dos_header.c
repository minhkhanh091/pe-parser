#include <stdio.h>

#include "model/dos_header.h"
#include "model/pe_file.h"

void parse_dos_header(PE_FILE* pe)
{
    memcpy(pe->dos_header, pe->buffer, sizeof(DOS_HEADER));
}

void print_dos_header(DOS_HEADER* dos_header)
{
    printf("DOS Header:\n");
    printf("e_magic: 0x%04x\n", dos_header->e_magic);
    printf("e_lfanew: 0x%08x\n", dos_header->e_lfanew);
}