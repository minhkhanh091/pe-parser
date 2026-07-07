#ifndef FILE_LOADER_H
#define FILE_LOADER_H

#include <stddef.h>
#include <stdint.h>

uint8_t* load_file_to_buffer(const char* file_name, size_t* file_sz);

#endif
