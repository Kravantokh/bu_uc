#include "benutils/unicode.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void print_uchar(char* c){
	while(*c != '\0'){
		fwrite(c, 1, sizeof(char), stdout);
		++c;
	}
}

char* encode_uchar(const char* s){
	/* Parsing the hex value */
	uint32_t bytes;
	sscanf(s, "U+%X", &bytes);

	/* Deciding how many bytes will be needed to store the character*/
	uint8_t length = 0;
	if(bytes <= 0x10FFFF)
		length = 4;
	if(bytes <= 0xFFFF)
		length = 3;
	if(bytes <= 0x7FF)
		length = 2;
	if(bytes <= 0x7F)
		length = 1;
	if(length == 0)
		return 0;

	/*Allocating those bytes and filling them with their corresponding data*/
	char* ret = (char*) malloc(length + 1);
	*(ret + length) = '\0';

	uint8_t i;
	for(i = length - 1; i > 0; --i){
		*(ret + i) = 0b10000000 | (0b00111111 & bytes);
		bytes >>= 6;
	}

	/* Settings the first byte's bits. A switch with fixed values should be faster than generating bit masks every time */
	switch(length){
		case 1:
			*ret = 0b01111111 & bytes;
			break;
		case 2:
			*ret = 0b11000000 | (0b00011111 & bytes);
			break;
		case 3:
			*ret = 0b11100000 | (0b00001111 & bytes);
			break;
		case 4:
			*ret = 0b11110000 | (0b00000111 & bytes);
			break;
	}

	return ret;
}
