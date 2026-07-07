/* 

NT Header structure definition for 64-bit PE files.

*/

#ifndef NT_HEADER_H
#define NT_HEADER_H

#include <stdint.h>

typedef struct PE_FILE PE_FILE;
typedef struct FILE_HEADER FILE_HEADER;
typedef struct OPTIONAL_HEADER OPTIONAL_HEADER;

typedef struct NT_HEADER
{
	uint32_t Signature;
	FILE_HEADER* FileHeader;
	OPTIONAL_HEADER* OptionalHeader;
} NT_HEADER;

#endif
