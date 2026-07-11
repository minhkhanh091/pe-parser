#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "loader/file_loader.h"
#include "model/pe_file.h"
#include "model/dos_header.h"
#include "model/import_directory.h"
#include "model/nt_header/nt_header.h"
#include "model/section_header.h"

static void cleanup(PE_FILE* pe)
{
    free_pe_file(pe);
}

int main(int argc, char* argv[])
{
    puts("PE File Parser 1.0\n");

    //if (argc <= 1)
    //{
    //    puts("Missing argument. Usage: ./pe-parser <file_path>");
    //    return 0;
    //}

    const char* file_name = "pe-parser.exe";
    //const char* file_name = argv[1];
    size_t file_sz = 0;
    uint8_t* buffer = load_file_to_buffer(file_name, &file_sz);

    PE_FILE pe;

    puts("Initializing PE File...\n");
    init_pe_file(&pe, buffer, file_sz);

    parse_dos_header(&pe);
    parse_nt_header(&pe);
    parse_section_header_array(&pe);
    init_import_directory(&pe);

	puts("\nPE File parsed successfully!\n");

    print_dos_header(pe.dos_header);
	print_nt_header(pe.nt_header);
	print_section_header(pe.section_header_array);
    print_import_directory(pe.import_directory);

	cleanup(&pe);

    return 0;
}