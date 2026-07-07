/* 

NT Header structure definition for 64-bit PE files.

*/

#ifndef NT_HEADER_H
#define NT_HEADER_H

#include <stdint.h>

typedef struct FILE_HEADER FILE_HEADER;

typedef struct NT_HEADER
{
	uint32_t Signature;
	FILE_HEADER* FileHeader;

} NT_HEADER;

#endif
