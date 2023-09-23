#include "shell.h"

/**
 * input_buf - Buffers chained commands and reads input.
 * @params: Pointer to a parameter struct.
 * @buffer: Pointer to the address of the input buffer.
 * @length: Pointer to the address of the length variable.
 *
 * Return: The number bytes read.
 */

	ssize_t input_buf(char **buffer, size_t *length, params_t *params)
	{
	ssize_t bytesRead = 0;
	size_t length_p = 0;

	if (!*length)
	{
	free(*buffer);
	*buffer = NULL;
	signal(SIGINT, sigintHandler);
#if USE_GETLINE
	bytesRead = getline(buffer, &length_p, stdin);
#else
	bytesRead = _getline(params, buffer, &length_p);
#endif
	if (bytesRead > 0)
	{
	if ((*buffer)[bytesRead - 1] == '\n')
	{
	(*buffer)[bytesRead - 1] = '\0';
	bytesRead--;
	}
	linecount_flag = 1;
	remove_comments(*buffer);
	build_history_list(params, *buffer, params->histcount++);
	{
	*length = bytesRead;
	params->cmd_buf = buffer;
	}
	}
	}
	return (bytesRead);
}

/**
 * get_input - Reads a line of input without the new line character.
 * @params: Pointer to the parameter struct.
 *
 * Return: The number of bytes read.
 */
	ssize_t get_input(params_t *params)
	{
	static char *buffer;
	static size_t p, r, length;
	ssize_t bytesRead = 0;
	char **buf_p = &(params->arg), *s;

	_putchar(BUF_FLUSH);
	bytesRead = input_buf(params, &buffer, &length);
	if (bytesRead == -1)
	return (-1);
	if (length)
	{
	r = p;
	s = buffer + p;

	check_chain(params, buffer, &r, p, length);
	while (r < length)
	{
	if (is_chain(params, buffer, &r))
	break;
	r++;
	}

	p = r + 1;
	if (p >= length)
	{
	p = length = 0;
	params->cmd_buf_type = CMD_NORM;
	}

	*buf_p = s;
	return (_strlen(s));
	}

	*buf_p = buffer;
	return (bytesRead);
}

/**
 * read_buf - Reads data input into a buffer.
 * @params: Pointer to a parameter struct.
 * @buffer: Pointer the buffer.
 * @p: Pointer to the size variable.
 *
 * Return: The number of bytes read.
 */

ssize_t read_buf(char *buffer, size_t *p, params_t *params)
{
	ssize_t bytesRead = 0;

	if (*p)
	return (0);
	bytesRead = read(params->readfd, buffer, READ_BUF_SIZE);
	if (bytesRead >= 0)
	*p = bytesRead;
	return (bytesRead);
}

/**
 * _getline - Reads the next line of input from STDIN.
 * @params: Pointer to a parameter struct.
 * @ptr: Address of the pointer to the buffer, preallocated or NULL.
 * @length: Size of the preallocated ptr buffer if not NULL.
 *
 * Return: The number of characters read.
 */

	int _getline(char **ptr, size_t *length, params_t *params)
	{
	static char buffer[READ_BUF_SIZE];
	static size_t p, len;
	size_t m;
	ssize_t bytesRead = 0, l = 0;
	char *s = NULL, *new_p = NULL, *i;

	s = *ptr;
	if (s && length)
	l = *length;
	if (p == len)
	p = len = 0;

	bytesRead = read_buf(params, buffer, &len);
	if (bytesRead == -1 || (bytesRead == 0 && len == 0))
	return (-1);

	i = _strchr(buffer + p, '\n');
	m = i ? 1 + (unsigned int)(i - buffer) : len;
	new_p = _realloc(s, l, l ? l + m : m + 1);
	if (!new_p)
	return (s ? free(s), -1 : -1);

	if (l)
	_strncat(new_p, buffer + p, m - p);
	else
	_strncpy(new_p, buffer + p, m - p + 1);

	l += m - p;
	p = m;
	s = new_p;

	if (length)
	*length = l;
	*ptr = p;
	return (l);
}

/**
 * sigintHandler - Blocks the Ctrl-C signal.
 * @sig_num: The signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
