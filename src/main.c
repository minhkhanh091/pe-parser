#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#include "loader/file_loader.h"
#include "model/pe_file.h"
#include "model/dos_header.h"


void processing()
{

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

    puts("Initializing PE File...");
    init_pe_file(&pe, buffer, file_sz);

    puts("Parsing DOS Header...\n");
    parse_dos_header(&pe);
	parse_nt_header_signature(&pe);

    is_pe_file_valid(&pe);

    print_dos_header(pe.dos_header);

    free_pe_file(&pe);

    return 0;
}