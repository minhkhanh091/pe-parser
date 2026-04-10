#ifndef DOSHEADER_H
#define DOSHEADER_H

struct DosHeader {
    __uint8_t magic[2];
    __uint8_t padding[62];
};

#endif