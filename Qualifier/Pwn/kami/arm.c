#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int kami() {
	char buffer[128];

	printf("Welcome to Africa battleCTF.!");
	fflush(stdout);

	gets(buffer);

}

int main(int argc, char** argv) {
	printf("fflush at %p\n", fflush);
	kami();

	return EXIT_SUCCESS;
}
