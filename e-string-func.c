#include"shell.h"

/**
 * custom_eputs - displays an input string
 * @str: the string to be displayed
 *
 * Return: Nothing
 */
void custom_eputs(char *str)
{
	int a = 0;

	if (!str)
		return;
	while (str[a] != '\0')
	{
		print_char_to_stderr(str[a]);
		a++;
	}
}

/**
 * print_string - Prints a string to the standard output
 * @str: The string to be printed
 *
 * Return: Nothing
 */
void print_string(char *str)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(2, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[a++] = c;
	return (1);
}

/**
 * write_to_fd - Writes the character c to the given file descriptor
 * @c: The character to print
 * @fd: The file descriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int write_to_fd(char c, int fd)
{
	static int a;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || a >= WRITE_BUF_SIZE)
	{
		write(fd, buf, a);
		a = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}

/**
 * _putsfd - Prints an input string to a file descriptor
 * @string: The string to be printed
 * @file_descriptor: The file descriptor to write to
 *
 * Return: The number of characters written
 */
int _putsfd(char *string, int file_descriptor)
{
	int character_count = 0;

	if (!string)
		return (0);
	while (*string)
	{
		character_count += write_to_fd(*string++, file_descriptor);
	}
	return (character_count);
}


