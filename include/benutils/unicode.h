
#ifndef __BU_UNICODE__
#define __BU_UNICODE__
/**\brief A struct to store a unicode character.
*/
struct tm_uchar{
	char* content;
};

typedef struct tm_uchar tm_uchar;

/** \brief Returns a \link tm_uchar tm_uchar\endlink struct containing the entered code.
* \param s The unicode code of the character you wish to store in the form
*/
tm_uchar tm_create_uchar(char* s);

#endif