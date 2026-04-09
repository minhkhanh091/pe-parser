#include <stdio.h>

#include "PeParser.h"
#include "loader/FileLoader.h"

PEFile *parse(const char *file_name) {
    PEFile *pe = new PEFile();

    load_file_to_buffer(pe, file_name);

    return pe;
}