#include "shell.h"

/**
 * _strncpy - Copies a string with a maximum of n characters.
 * @dest: The destination string to copy to.
 * @src: The source string to from.
 * @n: The maximum of characters to copy.
 *
 * Return: A pointer to the destination string (dest).
 */

	char *_strncpy(char *dest, char *src, int n)
	{
	int p;

	for (p = 0; p < n && src[p] != '\0'; p++)
	dest[p] = src[p];

	/* If the source string is shorter than n, pad with null characters. */
	for (; p < n; p++)
	dest[p] = '\0';

	return (dest);
	}

/**
 * _strncat - Concatenates two strings with a maximum of n bytes from src.
 * @dest: The first string src will be concatenated to.
 * @src: The second string to concatenate to dest.
 * @n: The maximum number of bytes to be used.
 *
 * Return: A pointer to the destination string (dest)
 */

	char *_strncat(char *dest, char *src, int n)
	{
	int dest_len = _strlen(dest);
	int p;

	for (p = 0; p < n && src[p] != '\0'; p++)
	dest[dest_len + p] = src[p];

	/* Null-terminate the concatenated string. */
	dest[dest_len + p] = '\0';

	return (dest);
}

/**
 * _strchr - Locates the first occurence of a character in a string.
 * @str: The string to be searched.
 * @c: The character to look for.
 *
 * Return: A pointer to the first occurrence of character c in str,
 *         or NULL if the character is not found.
 */

char *_strchr(char *str, char c)
	{
	while (*str != '\0')
	{
	if (*str == c)
	return (str);
	str++;
	}

	return (NULL);
	}
