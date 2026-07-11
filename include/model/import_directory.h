#ifndef IMPORT_DIRECTORY_H
#define IMPORT_DIRECTORY_H

#include <stdint.h>

typedef struct PE_FILE PE_FILE;

typedef struct IMPORT_FUNCTION
{
    char* name;
    uint16_t hint;
    uint64_t ordinal;
    uint8_t is_ordinal;
} IMPORT_FUNCTION;

typedef struct IMPORT_DESCRIPTOR
{
    uint32_t original_first_thunk;
    uint32_t time_date_stamp;
    uint32_t forwarder_chain;
    uint32_t name_rva;
    uint32_t first_thunk;

    char* dll_name;
    IMPORT_FUNCTION* functions;
    uint32_t function_count;
} IMPORT_DESCRIPTOR;

typedef struct IMPORT_DIRECTORY
{
    IMPORT_DESCRIPTOR* descriptors;
    uint32_t count;
} IMPORT_DIRECTORY;

void init_import_directory(PE_FILE* pe);
void free_import_directory(IMPORT_DIRECTORY* import_directory);
void print_import_directory(IMPORT_DIRECTORY* import_directory);

#endif
