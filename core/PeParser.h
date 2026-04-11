#ifndef PE_PARSER_H
#define PE_PARSER_H

#include <map>

#include "core/PEFile.h"
#include "model/DirectoryParser.h"

class PEParser {
    private:
        std::map<int, DirectoryParser *> directories;
    public:
        PEFile *parse(const char *file_name);
        void parse_dos_header(PEFile *pe);
};



#endif