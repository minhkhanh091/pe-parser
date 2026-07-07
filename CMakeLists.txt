cmake_minimum_required(VERSION 3.20)

project(pe-parser LANGUAGES C)

add_executable(pe-parser
    src/main.c
    src/loader/file_loader.c
    src/model/pe_file.c
)

target_include_directories(pe-parser PRIVATE
    include
)

set_target_properties(pe-parser PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED ON
)