
#include "string_functions.h"

/*
Name:	stringlength
Description:	This function gives the length of a string which is ended by the \0 character.
Parameters:	buf - character array representing the string
ReturnValue:	Length of the string.
*/
int stringlength(char *buf)
{
	int nReturnValue = 0;
	int i = 0;
	if(0 == buf)
		return nReturnValue;
	
	while(buf[i++] != '\0')
		nReturnValue++;

	return nReturnValue;
}
