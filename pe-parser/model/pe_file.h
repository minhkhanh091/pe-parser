#ifndef PE_FILE_H
#define PE_FILE_H

#include <stdint.h>

#include "dos_header.h"

typedef struct PE_FILE
{
	uint8_t* buffer;
	size_t size;

	DOS_HEADER* dos_header;

} PE_FILE;

void init_pe_file(PE_FILE* pe, uint8_t* buffer, size_t size);
void free_pe_file(PE_FILE* pe);
void is_pe_file_valid(PE_FILE* pe);

#endif
