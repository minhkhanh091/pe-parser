#ifndef PE_PARSER_H
#define PE_PARSER_H

#include "core/PEFile.h"

PEFile *parse(const char *file_name);

void parse_dos_header(PEFile *pe);

#endif