#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

#include "model/dos_header.h"
#include "model/import_directory.h"
#include "model/pe_file.h"
#include "model/nt_header/nt_header.h"
#include "model/section_header.h"

void init_pe_file(PE_FILE* pe, uint8_t* buffer, size_t size)
{
    pe->buffer = buffer;
    pe->size = size;
   pe->dos_header = (DOS_HEADER*)calloc(1, sizeof(DOS_HEADER));
    pe->nt_header = (NT_HEADER*)calloc(1, sizeof(NT_HEADER));
    pe->section_header_array = (SECTION_HEADER_ARRAY*)calloc(1, sizeof(SECTION_HEADER_ARRAY));
    pe->import_directory = (IMPORT_DIRECTORY*)calloc(1, sizeof(IMPORT_DIRECTORY));
}

void free_pe_file(PE_FILE* pe)
{
   free(pe->dos_header);
    free(pe->nt_header);
    free(pe->section_header_array);
    free_import_directory(pe->import_directory);
    free(pe->import_directory);
    free(pe->buffer);
    pe->dos_header = NULL;
    pe->nt_header = NULL;
    pe->section_header_array = NULL;
    pe->import_directory = NULL;
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