#ifndef PE_FILE_H
#define PE_FILE_H

#include "model/DOSHeader.h"

class PEFile {
    public:
        __uint8_t *buffer;
        int size;

        DosHeader *dos_header;

    PEFile(__uint8_t *buffer, int size) {
        this->buffer = buffer;
        this->size = size;
    }
};

#endif