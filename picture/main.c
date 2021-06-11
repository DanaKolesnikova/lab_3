#include "bmp.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
	if (argc > 1)
		read(argv[1], argv[2]);
	else
		printf("Not arguments");
	return 0;
}