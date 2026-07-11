#ifndef IMPORT_DIRECTORY_H
#define IMPORT_DIRECTORY_H

#include <stdint.h>

typedef struct PE_FILE PE_FILE;

typedef struct IMPORT_DIRECTORY_ENTRY
{
	uint32_t original_first_thunk;
	uint32_t time_date_stamp;
	uint32_t forwarder_chain;
	uint32_t name;
	uint32_t first_thunk;
} IMPORT_ENTRY;

typedef struct IMPORT_DIRECTORY_ARRAY
{
	IMPORT_ENTRY* entries;
	uint32_t count;
} IMPORT_DIRECTORY;

void init_import_directory(PE_FILE* pe);

#endif
