#include "shell.h"

/**
 * _strcpy - Function to copy a string.
 * @dest: The destination buffer to copy the string into.
 * @src: The source string to be copied.
 *
 * Return: Pointer to the destination buffer.
 */

	char *_strcpy(char *dest, char *src)
	{
	int p = 0;

	if (dest == src || src == 0)
	return (dest);
	while (src[p])
	{
	dest[p] = src[p];
	p++;
	}
	dest[p] = '\0';
	return (dest);
}

/**
 * _strdup - Function to duplicate a string.
 * @str: The string to be duplicated.
 *
 * Return: Pointer to the duplicated string or NULL if memory allocation fails.
 */

char *_strdup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
	return (NULL);
	while (*str++)
	length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
	return (NULL);
	for (length++; length--;)
	ret[length] = *--str;
	return (ret);
}

/**
 * _puts - Prints an input string to the standard output.
 * @str: The string to be printed.
 *
 * Return: Nothing.
 */

	void _puts(char *str)
	{
	int p = 0;

	if (!str)
	return;
	while (str[p] != '\0')
	{
	_putchar(str[p]);
	p++;
	}
	}

/**
 * _putchar - Writes the character to the standard output.
 * @c: The character to print.
 *
 * Return: On success 1. On error -1 , and errno is set appropriately.
 */

	int _putchar(char c)
	{
	static int p;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || p >= WRITE_BUF_SIZE)
	{
	write(1, buf, p);
	p = 0;
	}
	if (c != BUF_FLUSH)
	buf[p++] = c;

	return (1);
	}

