#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "loader/file_loader.h"

uint8_t* load_file_to_buffer(const char* file_name, size_t* file_sz) {
    FILE* fp = fopen(file_name, "rb");

    if (!fp) {
        printf("[ERROR] An error occured when opening file!!");
        exit(0);
    }

    /* Caculate file size */
    fseek(fp, 0, SEEK_END);
    *file_sz = ftell(fp);
    rewind(fp);

    /* Read file bytes file buffer */
    uint8_t* buffer = (uint8_t*)malloc(*file_sz);
    fread(buffer, 1, *file_sz, fp);

    return buffer;
}