#include"shell.h"
i
/**
 * get_history_filename -find file name history
 * @params: struct parameter
 *
 * Return: distribute string which contains file name history
 */
char *get_history_filename(params_t *params)
{
	char *buf, *dir;

	dir = _getenv(params, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}


/**
 * write_history_to_file -initiate a file or modify to already existing file
 * @params: struct the parameter
 *
 * Return: 1 on success, -1 else
 */
int write_history_to_file(params_t *params)
{
	ssize_t fd;
	char *filename = get_history_filename(params);
	list_t *node = NULL;

	if (!filename)
		return (-1);
	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = params->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putsfd("\n", fd);
	}
	_putsfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history_from_file - reads file history
 * @params: struct the parameter
 *
 * Return: success histcount, otherwise 0
 */
int read_history_from_file(params_t *params)
{
	int a, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_filename(params);

	if (!filename)
		return (0);

	fd = open(filename, O_RDONLY);
	free(filename);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		 fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd);
	for (a = 0; a < fsize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			build_history_list(params, buf + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		build_history_list(params, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (params->histcount-- >= HIST_MAX)
		delete_node_at_index(&(params->history), 0);
	renumber_history(params);
	return (params->histcount);
}

/**
 * build_history_list - add entry to history list linked
 * @params: Structure carries arguments.to maintain
 * @buf: buffer
 * @linecount: hiscount,the history line
 *
 * Return: 0 Always
 */
int build_history_list(params_t *params, char *buf, int linecount)
{
	list_t *node = NULL;

	if (params->history)
		node = params->history;
	add_node_end(&node, buf, linecount);

	if (!params->history)
		 params->history = node;
	 return (0);
}


/**
 * renumber_history - renumbers history link list once changes is made
 * @params: Structure carries arguments.to maintain
 *
 * Return: the new histcount
 */
int renumber_history(params_t *params)
{
	list_t *node = params->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}

