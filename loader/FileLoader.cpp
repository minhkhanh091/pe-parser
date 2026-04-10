#include <stdio.h>
#include <stdlib.h>

#include "FileLoader.h"

__uint8_t *load_file_to_buffer(const char *file_name, size_t *size) {
    FILE *fp = fopen(file_name, "rb");

    if (!fp) {
        printf("[ERROR] An error occured when opening file!!");
        exit(0);
    }

    /* Caculate file size */
    fseek(fp, 0, SEEK_END);
    *size = ftell(fp);
    rewind(fp);

    /* Read file bytes file buffer */
    __uint8_t *buffer = (__uint8_t *)malloc(*size);
    fread(buffer, 1, *size, fp);

    return buffer;
}