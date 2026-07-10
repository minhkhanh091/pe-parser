#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "model/nt_header/nt_header.h"
#include "model/nt_header/file_header.h"
#include "model/nt_header/opt_header.h"
#include "model/pe_file.h"
#include "model/dos_header.h"
#include "model/section_header.h"

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
	memcpy(pe->nt_header->OptionalHeader, pe->buffer + pe->dos_header->e_lfanew + sizeof(uint32_t) + sizeof(FILE_HEADER), sizeof(OPTIONAL_HEADER));
}

static void init_nt_header(NT_HEADER* nt_header)
{
	nt_header->Signature = 0;
	nt_header->FileHeader = (FILE_HEADER*)malloc(sizeof(FILE_HEADER));
	nt_header->OptionalHeader = (OPTIONAL_HEADER*)malloc(sizeof(OPTIONAL_HEADER));
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
	parse_optional_header(pe);
}

void print_nt_header(NT_HEADER* nt_header)
{
	printf("NT Header:\n");
	printf("Signature: 0x%08x\n", nt_header->Signature);
	print_file_header(nt_header->FileHeader);
	print_optional_header(nt_header->OptionalHeader);
}

void print_file_header(FILE_HEADER* file_header)
{
	puts("File Header:");
	printf("Machine: 0x%04x\n", file_header->Machine);
	printf("NumberOfSections: %u\n", file_header->NumberOfSections);
}

void print_optional_header(OPTIONAL_HEADER *opt_header)
{



	/* Displaying data directory entries */
	
	puts("Data Directory:");
	for (uint8_t idx = 0; idx < 16; ++idx)
	{
		printf("%s\n", DATA_DIRECTORY_NAMES[idx]);
		printf("	- Virtual Address: 0x%x\n", opt_header->DataDirectory[idx].VirtualAddress);
		printf("	- Size: 0x%x\n", opt_header->DataDirectory[idx].Size);
	}
}