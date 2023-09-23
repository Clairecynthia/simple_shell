#include "shell.h"

/**
 * _strlen - Calculates the length of a string.
 * @str: The input string.
 *
 * Return: The length of the string as an integer.
 */

	int _strlen(char *str)
	{
	int p = 0;

	if (!str)
	return (0);

	while (*str++)
	p++;
	return (p);
	}

/**
 * _strcmp - Compares two strings lexicographically.
 * @str1: The first string.
 * @str2: The second string.
 *
 * Return:
 *   - Negative value if str1 < str2.
 *   - Positive value if str1 > str2.
 *   - Zero if str1 is equal to str2.
 */

	int _strcmp(char *str1, char *str2)
	{
	while (*str1 && *str2)
	{
	if (*str1 != *str2)
	return (*str1 - *str2);
	str1++;
	str2++;
	}
	if (*str1 == *str2)
	return (0);
	else
	return (*str1 < *str2 ? -1 : 1);
	}

/**
 * starts_with - Checks if a substring starts with another string.
 * @str1: The string to search within.
 * @str2: The substring to find at the beginning of the str1.
 *
 * Return:
 *   - Address of the next character in str1 after the matching substring, or
 *   - NULL if the substring is not found at the beginning of str1.
 */

	char *starts_with(const char *str1, const char *str2)
	{
	while (*str2)
	if (*str2++ != *str1++)
	return (NULL);
	return ((char *)str1);
	}

/**
 * _strcat - Concatenates two strings.
 * @dest: The destination buffer where the strings will be concatenated.
 * @src: The source buffer, whose content will be appended to dest.
 *
 * Return: A pointer to the destination buffer (dest).
 */

char *_strcat(char *dest, char *src)
	{

	while (*dest)
	dest++;
	while (*src)
	*dest++ = *src++;
	*dest = *src;
	return (dest);
	}
