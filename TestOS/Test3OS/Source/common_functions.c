/************************************************************************************************************************************************************************************************************
 * Name: common_functions.c
 * Description: This file will have utilitiy functions that will be used by all the modules
 * References: from james molley tutorial
 * Date: 2/12/2017
************************************************************************************************************************************************************************************************************/


void memcpy(unsigned int *dest, const unsigned int *src, unsigned int len)
{
    const unsigned int *sp = (const unsigned int *)src;
    unsigned int *dp = (unsigned int *)dest;
    for(; len != 0; len--) *dp++ = *sp++;
}


void memset(unsigned int *dest, unsigned int val, unsigned int len)
{
    unsigned int *temp = (unsigned int *)dest;
    for ( ; len != 0; len--) *temp++ = val;
}
