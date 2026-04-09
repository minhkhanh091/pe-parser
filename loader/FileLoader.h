#ifndef FILEHEADER_H
#define FILEHEADER_H

#include "core/PEFile.h"

void load_file_to_buffer(PEFile *pe, const char *file_name);

#endif