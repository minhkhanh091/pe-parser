#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "model/import_directory.h"
#include "model/pe_file.h"
#include "model/nt_header/nt_header.h"
#include "model/nt_header/opt_header.h"
#include "model/section_header.h"

typedef struct IMAGE_IMPORT_DESCRIPTOR
{
    uint32_t OriginalFirstThunk;
    uint32_t TimeDateStamp;
    uint32_t ForwarderChain;
    uint32_t Name;
    uint32_t FirstThunk;
} IMAGE_IMPORT_DESCRIPTOR;

typedef struct IMAGE_THUNK_DATA64
{
    uint64_t AddressOfData;
} IMAGE_THUNK_DATA64;

static size_t rva_to_offset(PE_FILE* pe, uint32_t rva)
{
    if (rva == 0)
    {
        return 0;
    }

    if (pe->section_header_array == NULL || pe->section_header_array->sections == NULL || pe->section_header_array->count == 0)
    {
        return (rva < pe->size) ? rva : 0;
    }

    for (uint16_t i = 0; i < pe->section_header_array->count; ++i)
    {
        SECTION_HEADER* section = &pe->section_header_array->sections[i];
        uint32_t section_start = section->VirtualAddress;
        uint32_t section_size = section->VirtualSize;
        if (section_size < section->SizeOfRawData)
        {
            section_size = section->SizeOfRawData;
        }

        if (rva >= section_start && rva < section_start + section_size)
        {
            uint32_t offset = section->PointerToRawData + (rva - section_start);
            return (offset < pe->size) ? offset : 0;
        }
    }

    return (rva < pe->size) ? rva : 0;
}

static char* copy_c_string_from_rva(PE_FILE* pe, uint32_t rva)
{
    size_t offset = rva_to_offset(pe, rva);
    if (offset == 0 || offset >= pe->size)
    {
        return NULL;
    }

    size_t length = 0;
    while (offset + length < pe->size && pe->buffer[offset + length] != '\0')
    {
        ++length;
    }

    char* result = (char*)malloc(length + 1);
    if (result == NULL)
    {
        return NULL;
    }

    memcpy(result, pe->buffer + offset, length);
    result[length] = '\0';
    return result;
}

static uint32_t count_import_descriptors(PE_FILE* pe, size_t offset, uint32_t directory_size)
{
    uint32_t count = 0;
    while (offset + sizeof(IMAGE_IMPORT_DESCRIPTOR) <= pe->size)
    {
        if (directory_size != 0 && count * sizeof(IMAGE_IMPORT_DESCRIPTOR) >= directory_size)
        {
            break;
        }

        IMAGE_IMPORT_DESCRIPTOR descriptor;
        memcpy(&descriptor, pe->buffer + offset, sizeof(descriptor));
        if (descriptor.OriginalFirstThunk == 0 && descriptor.TimeDateStamp == 0 && descriptor.ForwarderChain == 0 && descriptor.Name == 0 && descriptor.FirstThunk == 0)
        {
            break;
        }

        ++count;
        offset += sizeof(IMAGE_IMPORT_DESCRIPTOR);
    }

    return count;
}

static uint32_t count_import_functions(PE_FILE* pe, uint32_t thunk_rva)
{
    uint32_t count = 0;
    size_t thunk_offset = rva_to_offset(pe, thunk_rva);
    if (thunk_offset == 0)
    {
        return 0;
    }

    while (thunk_offset + sizeof(IMAGE_THUNK_DATA64) <= pe->size)
    {
        IMAGE_THUNK_DATA64 thunk;
        memcpy(&thunk, pe->buffer + thunk_offset, sizeof(thunk));
        if (thunk.AddressOfData == 0)
        {
            break;
        }

        ++count;
        thunk_offset += sizeof(IMAGE_THUNK_DATA64);
    }

    return count;
}

static void parse_import_functions(PE_FILE* pe, IMPORT_DESCRIPTOR* descriptor)
{
    uint32_t thunk_rva = descriptor->original_first_thunk != 0 ? descriptor->original_first_thunk : descriptor->first_thunk;
    descriptor->function_count = count_import_functions(pe, thunk_rva);
    if (descriptor->function_count == 0)
    {
        descriptor->functions = NULL;
        return;
    }

    descriptor->functions = (IMPORT_FUNCTION*)calloc(descriptor->function_count, sizeof(IMPORT_FUNCTION));
    if (descriptor->functions == NULL)
    {
        descriptor->function_count = 0;
        return;
    }

    size_t thunk_offset = rva_to_offset(pe, thunk_rva);
    for (uint32_t i = 0; i < descriptor->function_count && thunk_offset + sizeof(IMAGE_THUNK_DATA64) <= pe->size; ++i)
    {
        IMAGE_THUNK_DATA64 thunk;
        memcpy(&thunk, pe->buffer + thunk_offset, sizeof(thunk));

        if (thunk.AddressOfData == 0)
        {
            descriptor->function_count = i;
            break;
        }

        if ((thunk.AddressOfData & 0x8000000000000000ULL) != 0)
        {
            descriptor->functions[i].is_ordinal = 1;
            descriptor->functions[i].ordinal = thunk.AddressOfData & 0xFFFFULL;
        }
        else
        {
            size_t name_offset = rva_to_offset(pe, (uint32_t)thunk.AddressOfData);
            if (name_offset != 0 && name_offset + sizeof(uint16_t) <= pe->size)
            {
                uint16_t hint = 0;
                memcpy(&hint, pe->buffer + name_offset, sizeof(uint16_t));
                descriptor->functions[i].hint = hint;
                descriptor->functions[i].name = copy_c_string_from_rva(pe, (uint32_t)thunk.AddressOfData + sizeof(uint16_t));
            }
        }

        thunk_offset += sizeof(IMAGE_THUNK_DATA64);
    }
}

static void parse_import_descriptor(PE_FILE* pe, IMPORT_DESCRIPTOR* descriptor, size_t offset)
{
    IMAGE_IMPORT_DESCRIPTOR raw_descriptor;
    memcpy(&raw_descriptor, pe->buffer + offset, sizeof(raw_descriptor));

    descriptor->original_first_thunk = raw_descriptor.OriginalFirstThunk;
    descriptor->time_date_stamp = raw_descriptor.TimeDateStamp;
    descriptor->forwarder_chain = raw_descriptor.ForwarderChain;
    descriptor->name_rva = raw_descriptor.Name;
    descriptor->first_thunk = raw_descriptor.FirstThunk;
    descriptor->dll_name = copy_c_string_from_rva(pe, raw_descriptor.Name);
    descriptor->functions = NULL;
    descriptor->function_count = 0;

    parse_import_functions(pe, descriptor);
}

void init_import_directory(PE_FILE* pe)
{
    if (pe == NULL || pe->import_directory == NULL || pe->nt_header == NULL || pe->nt_header->OptionalHeader == NULL)
    {
        return;
    }

    IMPORT_DIRECTORY* import_directory = pe->import_directory;
    import_directory->descriptors = NULL;
    import_directory->count = 0;

    const uint32_t directory_index = 1;
    uint32_t directory_rva = pe->nt_header->OptionalHeader->DataDirectory[directory_index].VirtualAddress;
    uint32_t directory_size = pe->nt_header->OptionalHeader->DataDirectory[directory_index].Size;
    if (directory_rva == 0 || directory_size == 0)
    {
        return;
    }

    size_t directory_offset = rva_to_offset(pe, directory_rva);
    if (directory_offset == 0)
    {
        return;
    }

    import_directory->count = count_import_descriptors(pe, directory_offset, directory_size);
    if (import_directory->count == 0)
    {
        return;
    }

    import_directory->descriptors = (IMPORT_DESCRIPTOR*)calloc(import_directory->count, sizeof(IMPORT_DESCRIPTOR));
    if (import_directory->descriptors == NULL)
    {
        import_directory->count = 0;
        return;
    }

    for (uint32_t i = 0; i < import_directory->count; ++i)
    {
        parse_import_descriptor(pe, &import_directory->descriptors[i], directory_offset + (i * sizeof(IMAGE_IMPORT_DESCRIPTOR)));
    }
}

void free_import_directory(IMPORT_DIRECTORY* import_directory)
{
    if (import_directory == NULL)
    {
        return;
    }

    for (uint32_t i = 0; i < import_directory->count; ++i)
    {
        IMPORT_DESCRIPTOR* descriptor = &import_directory->descriptors[i];
        free(descriptor->dll_name);
        descriptor->dll_name = NULL;

        for (uint32_t j = 0; j < descriptor->function_count; ++j)
        {
            free(descriptor->functions[j].name);
            descriptor->functions[j].name = NULL;
        }

        free(descriptor->functions);
        descriptor->functions = NULL;
    }

    free(import_directory->descriptors);
    import_directory->descriptors = NULL;
    import_directory->count = 0;
}

static void print_import_function(const IMPORT_FUNCTION* function)
{
    if (function->is_ordinal)
    {
        printf("\t\tOrdinal: %llu\n", (unsigned long long)function->ordinal);
        return;
    }

    printf("\t\tHint: %u\n", function->hint);
    printf("\t\tName: %s\n", function->name != NULL ? function->name : "<unnamed>");
}

void print_import_directory(IMPORT_DIRECTORY* import_directory)
{
    if (import_directory == NULL || import_directory->count == 0)
    {
        puts("Import Directory: <empty>");
        return;
    }

    puts("Import Directory:");
    for (uint32_t i = 0; i < import_directory->count; ++i)
    {
        IMPORT_DESCRIPTOR* descriptor = &import_directory->descriptors[i];
        printf("DLL: %s\n", descriptor->dll_name != NULL ? descriptor->dll_name : "<unnamed>");
        for (uint32_t j = 0; j < descriptor->function_count; ++j)
        {
            print_import_function(&descriptor->functions[j]);
        }
        puts("");
    }
}
