#ifndef __BU_UNICODE__
#define __BU_UNICODE__

#include <stdint.h>

/** \brief A function that prints out a unicode character pointed to by a char*.
*
* \param c The unicode character to be printed.
*/
void print_uchar(char* c);

/** \brief Encodes a unicode character into the given buffer. The buffer should have a length of at least 4 characters.
* \param string - string containing the character to be encoded into unicode (in U+DIGITS format)
* \param location - the buffer where the result should be stored.
*/
int encode_uchar(const char* string, char* location);

/** \brief Returns a *__char\*__* pointer to the bytes that encode the gicen character
* \param s The unicode code of the character you wish to store in the form U+DIGITS, where digits represents the hex digits of the unicode character in capital letters.
*/
char* allocate_uchar(const char* s);

/** \brief Unicode string struct
* Best used with \link allocate_ustring allocate_ustrin\endlink and \link print_ustring print_ustring\endlink
*/

typedef struct{
	/* Null-terminated array of bytes to represent the string's contents. */
	uint8_t* contents;
	/* Pointers to the beginning of each character. This also contains a null termination. */
	uint8_t** chars;
	/* The number of characters in the string */
	uint32_t length;
} ustring;


/** \brief A function to encode unicode strings.
* \param string - string to be encoded with U+DIGITS format for every character.
* Example usage:
* ```
* ustring str = allocate_ustring("U+00BB U+00BBU+00BB")
* ```
* This will allocate a string which containts: "»»»".
* Return value tells you the number of bytes written to stdout.
* You may also print only one of its characters by writing:
* ```
* print_uchar(str.chars[0]); //print first character
* print_uchar(str.chars[1]); //print second character
* ```
*/
ustring allocate_ustring(const char* string);

/* \brief A function to print a unicode string
* \param string - the string to be printed
*/
int print_ustring(ustring string);

#endif
