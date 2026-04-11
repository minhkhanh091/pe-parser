#ifndef IMPORT_PARSER_H
#define IMPORT_PARSER_H

#include <stdio.h>

#include "model/DirectoryParser.h"

class ImportParser : public DirectoryParser {
    public:
        void parse() {
            printf("Parsing Import Directory\n");
        }

    ImportParser() {
        printf("Import Parser created\n");
    }
};

#endif