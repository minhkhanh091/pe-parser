#include <stdio.h>
#include <map>

#include "PeParser.h"
#include "loader/FileLoader.h"
#include "model/DOSHeader.h"
#include "model/DirectoryParser.h"
#include "model/ImportParser.h"

using namespace std;

void PEParser::parse_dos_header(PEFile *pe) {
    pe->dos_header = (DosHeader *) (pe->buffer);
}

PEFile *PEParser::parse (const char *file_name) {
    size_t size;
    __uint8_t *buffer = load_file_to_buffer(file_name, &size);

    PEFile *pe = new PEFile(buffer, size);

    parse_dos_header(pe);

    /* Parse Directory Data */
    directories[1] = new ImportParser();

    return pe;
}