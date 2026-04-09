#include <stdio.h>
#include <stdlib.h>

#include "FileLoader.h"

void load_file_to_buffer(PEFile *pe, const char *file_name) {
    int file_size = 0;

    FILE *fp = fopen(file_name, "r");

    if (!fp) {
        printf("[ERROR] An error occured when opening file!!");
        exit(0);
    }

    /* Caculate file size */
    fseek(fp, 0, SEEK_END);
    file_size = ftell(fp);
    rewind(fp);

    /* Read file bytes file buffer */
    char *file_bytes = (char *)malloc(file_size);
    fread(file_bytes, 1, file_size, fp);

    pe->file_bytes = file_bytes;
    pe->file_size = file_size;
}