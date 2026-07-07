project(pe-parser C)

add_executable(pe-parser
    pe-parser.c
    loader/file_loader.c
    model/pe_file.c
    model/dos_header.c
 "model/nt_header/nt_header.h" "model/nt_header/nt_header.c" "model/nt_header/file_header.h")

set_target_properties(pe-parser PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED YES
)