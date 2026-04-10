#ifndef FILEHEADER_H
#define FILEHEADER_H

#include "core/PEFile.h"

__uint8_t *load_file_to_buffer(const char *file_name, size_t *size);

#endif