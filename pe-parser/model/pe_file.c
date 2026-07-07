#include <stdio.h>
#include <stdlib.h>

#include "pe_file.h"

void init_pe_file(PE_FILE* pe, uint8_t* buffer, size_t size)
{
    pe->buffer = buffer;
    pe->size = size;
    pe->dos_header = NULL;
}

void free_pe_file(PE_FILE* pe)
{
    free(pe->dos_header);
    free(pe->buffer);
    pe->dos_header = NULL;
    pe->buffer = NULL;
    pe->size = 0;
}

void is_pe_file_valid(PE_FILE* pe)
{
    if (pe->dos_header->e_magic != 0x5A4D)
    {
        puts("[ERROR] Invalid PE file: incorrect DOS header magic number.\n");

		free_pe_file(pe);
        exit(0);
    }
}