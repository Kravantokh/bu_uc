#include "benutils/unicode.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

void print_uchar(char* c){
	if(c == 0)
		return;
	uint8_t firstbyte = *c;
	uint8_t length = 0;
	/* If the first bit is 0 it is 1 byte */
	if( !(firstbyte >> 7) )
		length = 1;
	/* Check the other possibilities */
	else if( (firstbyte >> 5) == 0b00000110)
		length = 2;
	else if( (firstbyte >> 4) == 0b00001110 )
		length = 3;
	else if( (firstbyte >> 3) == 0b00011110 )
		length = 4;
	else length = 0;

	if(length)
		fwrite(c, 1, length, stdout);
}

/*Not null-terminated since the first byte tells us the length and thus now memory is wasted.*/
char* allocate_uchar(const char* s){
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
	/*Allocating those bytes and filling them with their corresponding data. It fills the free bits from right to left. If the character has only one byte this for is not entered.*/
	char* ret = (char*) malloc(length);

	uint8_t i;
	for(i = length - 1; i > 0; --i){
		*(ret + i) = 0b10000000 | (0b00111111 & bytes);
		bytes >>= 6;
	}

	/* Settings the first byte's bits. A switch with fixed values should be faster than generating bit masks every time.
	This will make sense if you check out the UTF-8 encoding specifications (the first byte gives the totatl size of the character in UTF-8). */
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

int get_encoded_length(const char* s){
	/* Parsing the hex value */
	uint32_t bytes;
	sscanf(s, "U+%X", &bytes);

	/* Deciding how many bytes will be needed to store the character and returning the value.*/
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
	return length;
}

/* The location must be of at least 4 bytes. string is the unicode code of the character. The return value tells the number of used bytes.*/
int encode_uchar(const char* string, char* location){
	/* Parsing the hex value */
	uint32_t bytes;
	sscanf(string, "U+%X", &bytes);

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


	uint8_t i;
	for(i = length - 1; i > 0; --i){
		*(location + i) = 0b10000000 | (0b00111111 & bytes);
		bytes >>= 6;
	}

	/* Settings the first byte's bits. A switch with fixed values should be faster than generating bit masks every time.
	This will make sense if you check out the UTF-8 encoding specifications (the first byte gives the totatl size of the character in UTF-8). */
	switch(length){
		case 1:
			*location = 0b01111111 & bytes;
			break;
		case 2:
			*location = 0b11000000 | (0b00011111 & bytes);
			break;
		case 3:
			*location = 0b11100000 | (0b00001111 & bytes);
			break;
		case 4:
			*location = 0b11110000 | (0b00000111 & bytes);
			break;

	}

	return length;
}

ustring allocate_ustring(const char* string){

	/* The length of the string must be measured in bytes to allocate the correct amount of memory.*/
	int num_bytes = 0; /* Size of the string in bytes*/
	int strlen = 0; /* Size of the string in number of character*/

	int i = 0;
	while(string[i] != 0){
		if(string[i] == 'U'){
			num_bytes += get_encoded_length(&string[i]); /*&string[i]*/
			strlen++;
		}
		++i;
	}

	uint8_t* encoded_contents = (uint8_t*) malloc( (num_bytes + 1)*sizeof(uint8_t) );
	uint8_t** chars = (uint8_t**) malloc( (strlen + 1)*sizeof(uint8_t*) );

	/* Add null terminations */
	encoded_contents[num_bytes] = 0;
	chars[strlen] = 0;
	/* Encoding the string.*/
	i = 0;
	int filled_bytes = 0;
	int filled_chars = 0;
	char temporary_char[4] = {0};

	while(string[i] != 0){
		if(string[i] == 'U'){
			int current_char_len = encode_uchar(&string[i], temporary_char);
			chars[filled_chars] = (encoded_contents + filled_bytes);
			memcpy( (encoded_contents + filled_bytes), temporary_char, current_char_len);
			filled_bytes += current_char_len;
			++filled_chars;
		}
		++i;
	}
	ustring ret;
	ret.contents = encoded_contents;
	ret.chars = chars;
	ret.length = strlen;
	return ret;
}

/* Return value gives you the number of bytes printed. */
int print_ustring(ustring string){
	int i = 0;
	while( string.contents[i] != 0){
		fwrite((string.contents + i), 1, 1, stdout);
		++i;
	}
	return i;
}
