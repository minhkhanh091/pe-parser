#ifndef DOS_HEADER_H
#define DOS_HEADER_H

#include <stdint.h>

typedef struct PE_FILE PE_FILE;

typedef struct DOS_HEADER
{
	/* Only listing important field */

	uint16_t e_magic;
	char unused[58];
	uint32_t e_lfanew;
} DOS_HEADER;

#endif
