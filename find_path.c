#include "shell.h"

/**
 * is_command - Checks if a file is an executable command.
 * @params: Pointer to the parameter struct.
 * @path: The path to the file to be checked.
 *
 * Return: 1 if the file is executable, 0 otherwise.
 */
	int is_command(char *path, param_t *params)
	{
	struct stat st;

	if (!path || stat(path, &st) != 0)
	return (0);

	if (st.st_mode & S_IFREG)
	{
	return (1);
	}
	return (0);
	}

/**
 * dup_chars - Duplicates characters from a string within a specified range.
 * @pathstr: The source string.
 * @begin: The starting index (inclusive).
 * @finish: The stopping index (exclusive).
 *
 * Return: Pointer to a new buffer containing the duplicated characters.
 */
	char *dup_chars(char *pathstr, int begin, int finish)
	{
	static char buf[1024];
	int p, m = 0;

	for (p = begin; p < finish; p++)
	{
	if (pathstr[p] != ':')
	buf[m++] = pathstr[p];
	}
	buf[m] = '\0';
	return (buf);
	}

/**
 * locate_path - Searches for a command in the PATH string.
 * @params: Pointer to the parameter struct (unused).
 * @pathstr: The PATH string containing directories.
 * @cmd: The command to find.
 *
 * Return: Full path of the command if found, or NULL.
 */
	char *locate_path(char *pathstr, char *cmd, param_t *params)
	{
	int p = 0, curr_pla = 0;
	char *path;

	if (!pathstr)
	return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
	if (is_cmd(params, cmd)
	return (cmd);
	}
	while (1)
	{
	if (!pathstr[p] || pathstr[p] == ':')
	{
	path = dup_chars(pathstr, curr_pla, p);
	if (!*path)
	_strcat(path, cmd);
	else
	{
	_strcat(path, "/");
	_strcat(path, cmd);
	}
	if (is_cmd(params, path))
	return (path);
	if (!pathstr[p])
	break;
	curr_pla = p;
	}
	p++;
	}
	return (NULL);
	}
