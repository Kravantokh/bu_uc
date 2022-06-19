#include <stdio.h>
#include <stdlib.h>
#include "benutils/unicode.h"

#ifdef WIN32
#include <windows.h>
#endif

int main(int argc, char* argv[]){
	#ifdef WIN32
	/* Set unicode encoding on windows and clear the message confirming the codepage switch*/
	SetConsoleOutputCP(65001);
	#endif

	printf("Test: \n");
	char* c = allocate_uchar("U+00BB");
	print_uchar(c);
	printf("\n");
	/* Spaces do not matter in the string. Only unicode characters coded in the U+DIGITS format are parsed. You may omit the space. I added them for readability.*/
	ustring str = allocate_ustring("U+03B7 U+03B5 U+03BB U+03BB U+03C9");

	print_ustring(str);

	free(c);
	return 0;
}
