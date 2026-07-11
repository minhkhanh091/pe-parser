#ifndef DATA_DIRECTORY_H

#include <stdint.h>

static const char* DATA_DIRECTORY_NAMES[16] = {
    "Export Table",
    "Import Table",
    "Resource Table",
    "Exception Table",
    "Certificate Table",
    "Base Relocation Table",
    "Debug Directory",
    "Architecture Specific Data",
    "Global Pointer Register (GPR) Relative Addressing Table",
    "Thread Local Storage (TLS) Table",
    "Load Configuration Table",
    "Bound Import Table",
    "Import Address Table (IAT)",
    "Delay Import Descriptor",
    "CLR Runtime Header",
    "Reserved"
};

typedef struct DATA_DIRECTORY
{
    uint32_t VirtualAddress;
    uint32_t Size;
} DATA_DIRECTORY;

#endif
