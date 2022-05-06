#include <stdio.h>
#include <stdlib.h>
#include "benutils/unicode.h"

int main(int argc, char* argv[]){
	char* c = encode_uchar("U+12060");
	print_uchar(c);
	free(c);
	return 0;
}
