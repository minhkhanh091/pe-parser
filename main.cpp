#include <stdio.h>

#include "loader/FileLoader.h"
#include "core/PeParser.h"
#include "core/PEFile.h"

void print_dos_header(PEFile *pe) {
	printf("DOS Header:\n");
	printf("	Magic: 0x%x%x\n", pe->dos_header->magic[0], pe->dos_header->magic[1]);
}

int main(int agc, char *agv[]) {
	PEFile *pe = parse("./PE-bear.exe");

	print_dos_header(pe);

	return 0;
}