
#include "cstring.h"

namespace sdds
{
	// Copies the srouce character string into the destination
	void strCpy(char* des, const char* src)
	{
		while ((*(des++) = *(src++)));
	}
	// Copies the source character string into the destination upto "len"
	// characters. The destination will be null terminated only if the number
	// of the characters copied is less than "len"
	void strnCpy(char* des, const char* src, int len)
	{
		int i, flag = 0;
		for (i = 0; i < len && flag == 0; i++)
		{
			des[i] = src[i];
			if (des[i] == '\0')
				flag = 1;
		}
		if (flag == 0)
			des[i] = '\0';
	}
	// Compares two C-strings 
	// returns 0 i thare the same
	// return > 0 if s1 > s2
	// return < 0 if s1 < s2
	int strCmp(const char* s1, const char* s2)
	{
		while (*s1 == *s2 && *s1 != '\0' && *s2 != '\0')
		{
			s1++;
			s2++;
		}
		return *s1 - *s2;
	}
	// returns 0 i thare the same
	// return > 0 if s1 > s2
	// return < 0 if s1 < s2
	int strnCmp(const char* s1, const char* s2, int len)
	{
		int count = 0;
		while (count < len && *s1 == *s2 && *s1 != '\0' && *s2 != '\0')
		{
			count++;
			if (count < len)
			{
				s1++;
				s2++;
			}
		}
		return *s1 - *s2;
	}
	// returns the lenght of the C-string in characters
	int strLen(const char* s)
	{
		int i = 0;
		for (i = 0; s[i] != '\0'; i++);
		return i;
	}
	// returns the address of first occurance of "str2" in "str1"
	// returns nullptr if no match is found
	const char* strStr(const char* str1, const char* str2)
	{
		int len = strLen(str2);
		int i, flag = 0;
		char* toReturn = nullptr;


		for (i = 0; str1[i] != '\0' && flag == 0; i++)
		{
			if (strnCmp(&str1[i], str2, len) == 0)
			{
				toReturn = (char*)&str1[i];
				flag = 1;
			}
		}
		return toReturn;
	}
	// Concantinates "src" C-string to the end of "des"
	void strCat(char* des, const char* src)
	{
		while (*(des))
		{
			des++;
		}
		while ((*(des++) = *(src++)));
	}
}