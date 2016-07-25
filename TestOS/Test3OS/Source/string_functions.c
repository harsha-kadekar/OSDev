/*******************************************************************************************************************************************
 Name: string_functions.c
 Description: This file will have all the functions which can be used operate on strings
 references: - 
 Date: 7/24/2016
*******************************************************************************************************************************************/

#include "string_functions.h"

// Name: string_length
// Description: This function will return the length of the \0 ended string
// parameter: buf - character array / string whose length needs to be calculated
// return: length of the string
int string_length(char *buf)
{
	int nLength = -1;
	if(buf == 0)
		return nLength;

	while(buf[nLength++] != '\0');

	return nLength;
}
