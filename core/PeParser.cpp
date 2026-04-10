#include <stdio.h>

#include "PeParser.h"
#include "loader/FileLoader.h"
#include "model/DOSHeader.h"

void parse_dos_header(PEFile *pe) {
    pe->dos_header = (DosHeader *) (pe->buffer);
}

PEFile *parse(const char *file_name) {
    size_t size;
    __uint8_t *buffer = load_file_to_buffer(file_name, &size);

    PEFile *pe = new PEFile(buffer, size);

    parse_dos_header(pe);

    return pe;
}