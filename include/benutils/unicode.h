
#ifndef __BU_UNICODE__
#define __BU_UNICODE__

/** \brief A function that prints out a unicode character stored in a \link tm_uchar tm_uchar\endlink with its set colors and transparency.
*
* \param c The colored unicode character to be printed.
*/
void print_uchar(char* c);

/** \brief Returns a \link tm_uchar tm_uchar\endlink struct containing the entered code.
* \param s The unicode code of the character you wish to store in the form
*/
char* encode_uchar(const char* s);

#endif
