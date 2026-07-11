cmake_minimum_required(VERSION 3.20)

project(pe-parser LANGUAGES C)

add_executable(pe-parser
    src/main.c
    src/loader/file_loader.c
    src/model/pe_file.c
 "src/model/nt_header/nt_header.c" "src/model/dos_header.c" "include/model/nt_header/data_directory.h" "include/model/section_header.h" "src/model/section_header.c" "src/model/import_directory.c")

target_include_directories(pe-parser PRIVATE
    include
)

set_target_properties(pe-parser PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
)