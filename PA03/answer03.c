#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<malloc.h>



char * strcat_ex(char * * dest, int * n, const char * src)
{
size_t src_len = strlen(src);
size_t dest_len = *dest == NULL ? 0 : strlen(*dest);
if (*dest == NULL || src_len + dest_len + 1 >= *n)
{
        *n = 1 + 2 * (src_len + dest_len);
        char *buffer = malloc(*n * sizeof(char));
        *buffer = '\0';
	if(*dest != NULL) strcpy(buffer, *dest);
	free(*dest);
	*dest = buffer;

}
	strcat(*dest, src);
	return *dest;
}

char * * explode(const char * str, const char * delims, int * arrLen);
{
does it work




}
