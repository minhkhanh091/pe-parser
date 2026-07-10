#ifndef SECTION_HEADER_H
#define SECTION_HEADER_H

#include <stdint.h>

typedef struct PE_FILE PE_FILE;

typedef struct SECTION_HEADER
{
	char Name[8];
	uint32_t VirtualSize;
	uint32_t VirtualAddress;
	uint32_t SizeOfRawData;
	uint32_t PointerToRawData;
	uint32_t PointerToRelocations;
	uint32_t PointerToLinenumbers;
	uint16_t NumberOfRelocations;
	uint16_t NumberOfLinenumbers;
	uint32_t Characteristics;
} SECTION_HEADER;

typedef struct SECTION_HEADER_ARRAY
{
	SECTION_HEADER *sections;
	uint16_t count;
} SECTION_HEADER_ARRAY;

//void free_section_header_array(SECTION_HEADER_ARRAY* section_header_array);

void parse_section_header_array(PE_FILE* pe);

void print_section_header(SECTION_HEADER_ARRAY * section_header_array);

#endif