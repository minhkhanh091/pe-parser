#include <stdio.h>
#include <stdlib.h>

#include "model/dos_header.h"
#include "model/pe_file.h"
#include "model/nt_header/nt_header.h"

void init_pe_file(PE_FILE* pe, uint8_t* buffer, size_t size)
{
    pe->buffer = buffer;
    pe->size = size;
    pe->dos_header = (DOS_HEADER*)malloc(sizeof(DOS_HEADER));
	pe->nt_header = (NT_HEADER*)malloc(sizeof(NT_HEADER));
}

void free_pe_file(PE_FILE* pe)
{
    free(pe->dos_header);
    free(pe->nt_header);
    free(pe->buffer);
    pe->dos_header = NULL;
	pe->nt_header = NULL;
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

    if (pe->nt_header->Signature != 0x00004550)
    {
        printf("[ERROR] Invalid PE file: incorrect NT header signature.\n");

        free_pe_file(pe);
        exit(0);
    }
}