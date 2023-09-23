#include "shell.h"

/**
 * **strtow - Splits a string into words, repeated delimiters are ignored.
 * @str: The input string.
 * @d: The delimiter string.
 * Return: A pointer to an array of strings, or NULL on failure.
 */

	char **strtow(char *str, char *d)
	{
	int p, r, m, q, wordcount = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
	return (NULL);

	if (!d)
	d = " ";

	for (p = 0; str[p] != '\0'; p++)
	{
	if (!is_delim(str[p], d) && (is_delim(str[p + 1], d) || !str[p + 1]))
	wordcount++;
	}

	if (wordcount == 0)
	return (NULL);

	s = malloc((wordcount + 1) * sizeof(char *));

	if (!s)
	return (NULL);

	for (p = 0, r = 0; r < wordcount; r++)
	{
	while (is_delim(str[p], d))
	p++;
	m = 0;
	while (!is_delim(str[p + m], d) && str[p + m])
	m++;

	s[r] = malloc((m + 1) * sizeof(char));

	if (!s[r])
	{
	for (m = 0; m < r; m++)
	free(s[m]);
	free(s);
	return (NULL);
	}

	for (q = 0; q < m; q++)
	s[r][q] = str[p++];

	s[r][q] = '\0';
	}

	s[r] = NULL;
	return (s);
	}

/**
 * **strtow2 - Splits a string into words using a single character delimiter.
 * @str: The input string.
 * @d: The delimiter character.
 * Return: A pointer to an array of strings, or NULL on failure.
 */

	char **strtow2(char *str, char d)
	{
	int p, r, m, q, wordcount = 0;
	char **s;

	if (str == NULL || str[0] == '\0')
	return (NULL);

	for (p = 0; str[p] != '\0'; p++) {
	if ((str[p] != d && str[p + 1] == d) ||
	(str[p] != d && !str[p + 1]) || str[p + 1] == d)
	wordcount++;
	}

	if (wordcount == 0)
	return (NULL);

	s = malloc((wordcount + 1) * sizeof(char *));

	if (!s)
	return (NULL);

	for (p = 0, r = 0; r < wordcount; r++)
	{
	while (str[p] == d && str[p] != '\0')
	p++;

	m = 0;
	while (str[p + m] != d && str[p + m] && str[p + m] != d)
	m++;

	s[r] = malloc((m + 1) * sizeof(char));

	if (!s[r])
	{
	for (m = 0; m < r; m++)
	free(s[m]);
	free(s);
	return (NULL);
	}

	for (q = 0; q < m; q++)
	s[r][q] = str[p++];

	s[r][q] = '\0';
	}

	s[r] = NULL;
	return (s);
	}
