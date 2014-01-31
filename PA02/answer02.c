#include<stdio.h>
#include<stdlib.h>

#include "answer02.h"

size_t my_strlen(const char * str)
{
	size_t count = 0;
	
	while(str[count] != '\0')
{	
	count++;
}
	return count;
}

int my_countchar(const char * str, char ch)
{
	int count = 0;
	while(!*str)
{
	if(*str == ch)
	count++;
	str++;
}
return count;
}
char * my_strchr(const char * str, int ch)
{	
	int count = 0;
	int length = my_strlen(str);

	while(count <= length)
{
	if(str[count] == ch)
	{	
	return(char *) &str[count];
	}
	count++;
}
	return NULL;
} 
char * my_strrchr(const char * str, int ch)
 {

	int length = my_strlen(str);
	int count = length + 1;
	while(count >= 0)
	{
	if(str[count] == ch)
	{
	return (char *) &str[count];
	}
	count--;
	}
return NULL;
}
char * my_strstr(const char * haystack, const char * needle)
{
	if (needle == '\0') return (char *) haystack;
	while(*haystack != '\0')
 {
	const char *l1 = haystack;
	const char *l2 = needle;
	while(*l1 == *l2 && *l1 != '\0' && *l2 != '\0')
	{
	l1++;
	l2++;
	}
 	if(*l2 == '\0') return (char*) haystack;
	haystack++;
}
return NULL;
}
char * my_strcpy(char * dest, const char * src)
{
	char *real = dest;
	while (*src) *dest++ = *src++;	
	*dest = '\0';
	return real;
}
char * my_strcat(char * dest, const char * src)
{
	my_strcpy(dest + my_strlen(dest), src);
	return dest;

}
int my_isspace(int ch)
{
	if (ch == ' ' || ch == '\f' || ch == '\n' || ch == '\r' || ch == '\t'|| ch == '\v')
	{	
	return 1;
	}
return 0;
}

int my_isdigit(int ch)
{
return (ch >= '0' && ch <= '9');
}
int my_atoi(const char * str)
{
	while(*str * my_isspace(*str))
	 str++;
	int sign = 1;
	if(*str == '-')
	{
	sign = -1;
	str++;
	}	
	int ret = 0;

	while (my_isdigit(*str))

	ret *= 10;
	ret += *str - '0';
	str++;	


return sign * ret;
}




















 

