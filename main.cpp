#include <stdio.h>

#include "loader/FileLoader.h"
#include "core/PeParser.h"
#include "core/PEFile.h"

int main(int agc, char *agv[]) {
	PEFile *pe = parse("PE-bear.exe");

	printf("%d", pe->file_size);
	
	return 0;
}