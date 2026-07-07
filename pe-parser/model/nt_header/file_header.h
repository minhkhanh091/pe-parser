#ifndef FILE_HEADER_H
#define FILE_HEADER_H

#include <stdint.h>

typedef struct FILE_HEADER
{
	uint16_t Machine;
	uint16_t NumberOfSections;
	uint32_t TimeDateStamp;
	uint32_t PointerToSymbolTable;
	uint32_t NumberOfSymbols;
	uint16_t SizeOfOptionalHeader;
	uint16_t Characteristics;
} FILE_HEADER;

#endif