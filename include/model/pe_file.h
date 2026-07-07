#ifndef PE_FILE_H
#define PE_FILE_H

#include <stdint.h>

typedef struct DOS_HEADER DOS_HEADER;
typedef struct NT_HEADER NT_HEADER;

typedef struct PE_FILE
{
	uint8_t* buffer;
	size_t size;

	DOS_HEADER* dos_header;
	NT_HEADER* nt_header;
} PE_FILE;

void init_pe_file(PE_FILE* pe, uint8_t* buffer, size_t size);
void free_pe_file(PE_FILE* pe);
void is_pe_file_valid(PE_FILE* pe);

void parse_dos_header(PE_FILE* pe);
void parse_nt_header_signature(PE_FILE* pe);

void print_dos_header(DOS_HEADER* dos_header);

#endif
