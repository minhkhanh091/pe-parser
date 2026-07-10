#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model/section_header.h"
#include "model/pe_file.h"
#include "model/nt_header/nt_header.h"
#include "model/nt_header/file_header.h"
#include "model/dos_header.h"

void parse_section_header_array(PE_FILE* pe)
{
	pe->section_header_array->count = pe->nt_header->FileHeader->NumberOfSections;
	pe->section_header_array->sections = (SECTION_HEADER*)malloc(sizeof(SECTION_HEADER) * pe->section_header_array->count);
	memcpy(pe->section_header_array->sections, pe->buffer + pe->dos_header->e_lfanew + sizeof(uint32_t) + sizeof(FILE_HEADER) + pe->nt_header->FileHeader->SizeOfOptionalHeader, sizeof(SECTION_HEADER) * pe->section_header_array->count);
}

static void __print_section_header(SECTION_HEADER* section_header)
{
	printf("Section Header:\n");
	printf("Name: %.8s\n", section_header->Name);
	printf("VirtualSize: 0x%08x\n", section_header->VirtualSize);
	printf("VirtualAddress: 0x%08x\n", section_header->VirtualAddress);
	printf("SizeOfRawData: 0x%08x\n", section_header->SizeOfRawData);
	printf("PointerToRawData: 0x%08x\n", section_header->PointerToRawData);
	printf("PointerToRelocations: 0x%08x\n", section_header->PointerToRelocations);
	printf("PointerToLinenumbers: 0x%08x\n", section_header->PointerToLinenumbers);
	printf("NumberOfRelocations: %u\n", section_header->NumberOfRelocations);
	printf("NumberOfLinenumbers: %u\n", section_header->NumberOfLinenumbers);
	printf("Characteristics: 0x%08x\n", section_header->Characteristics);
}

void print_section_header(SECTION_HEADER_ARRAY *section_header_array)
{
	for (uint16_t i = 0; i < section_header_array->count; i++)
	{
		__print_section_header(&section_header_array->sections[i]);
		puts("");
	}
}