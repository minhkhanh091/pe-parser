#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "model/nt_header/nt_header.h"
#include "model/nt_header/file_header.h"
#include "model/nt_header/opt_header.h"
#include "model/pe_file.h"
#include "model/dos_header.h"

static void parse_signature(PE_FILE* pe)
{
	pe->nt_header->Signature = *(uint32_t*)(pe->buffer + pe->dos_header->e_lfanew);
}

static void parse_file_header(PE_FILE* pe)
{
	memcpy(pe->nt_header->FileHeader, pe->buffer + pe->dos_header->e_lfanew + sizeof(uint32_t), sizeof(FILE_HEADER));
	
}

static void parse_optional_header(PE_FILE* pe)
{
	pe->nt_header->OptionalHeader = (OPTIONAL_HEADER*)(pe->buffer + pe->dos_header->e_lfanew + sizeof(uint32_t) + sizeof(FILE_HEADER));
}

void init_nt_header(NT_HEADER* nt_header)
{
	nt_header->Signature = 0;
	nt_header->FileHeader = (FILE_HEADER*)malloc(sizeof(FILE_HEADER));
	// nt_header->OptionalHeader = (OPTIONAL_HEADER*)malloc(sizeof(OPTIONAL_HEADER));
}

void parse_nt_header(PE_FILE *pe)
{
	init_nt_header(pe->nt_header);

	// Parsing the NT header signature
	puts("Parsing NT Header Signature...");
	parse_signature(pe);
	is_pe_file_valid(pe);

	// Parsing the File Header
	puts("Parsing File Header...");

	parse_file_header(pe);

	// Parsing the Optional Header
	puts("Parsing Optional Header...");
	// parse_optional_header(pe);
}