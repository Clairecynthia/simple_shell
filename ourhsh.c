#include "shell.h"

/**
 * ourhsh - Main function for the shell loop
 * @params: Pointer to the shell information struct
 * @av: Argument vector containing command line arguments
 *
 * Return: 0 on success, 1 on error, or error code.
 */
	int ourhsh(char **av, params_t *params)
	{
	ssize_t d = 0;
	int custom_ret = 0;

	while (d != -1 && custom_ret != -2)
	{
	clear_params(params);
	if (interactive(params))
	_puts("$ ");
	_eputchar(BUF_FLUSH);
	d = get_input(params);
	if (d != -1)
	{
	set_params(params, av);
	custom_ret = find_custom(params);
	if (custom_ret == -1)
	find_command(params);
	}
	else if (interactive(params))
	_putchar('\n');
	free_params(params, 0);
	}
	write_history(params);
	free_params(params, 1);
	if (!interactive(params) && params->status)
	exit(status);
	if (custom_ret == -2)
	{
	if (params->err_num == -1)
	exit(params->status);
	exit(1);
	}
	return (custom_ret);
	}

/**
 * find_custom - Looks for a custom command in the shell
 * @params: Pointer to the shell information struct
 *
 * Return: -1 if custom command not found,
 *         0 if custom command executed successfully,
 *         1 if custom command found but not successful,
 *         -2 if custom command signals exit()
 */
	int find_custom(params_t *params)
	{
	int p, custom_ret = -1;
	custom_table customtbl[] = {
	{"exit", _isexit},
	{"env", _isenv},
	{"help", _ishelp},
	{"history", _ishistory},
	{"setenv", _issetenv},
	{"unsetenv", _isunsetenv},
	{"cd", _iscd},
	{"alias", _isalias},
	{NULL, NULL}
	};

	for (p = 0; customtbl[p].type; p++)
	if (_strcmp(params->argv[0], customtbl[p].type) == 0)
	{
	params->line_count++;
	custom_ret = customtbl[p].func(params);
	break;
	}
	return (custom_ret);
	}

/**
 * find_command - Looks for an executable command in the system's PATH
 * @params: Pointer to the shell information struct
 *
 * Return: void
 */
	void find_command(params_t *params)
	{
	char *path = NULL;
	int p, m;

	params->path = params->argv[0];
	if (params->linecount_flag == 1)
	{
	params->line_count++;
	params->linecount_flag = 0;
	}
	for (p = 0, m = 0; params->arg[p]; p++)
	if (!is_delim(params->arg[p], " \t\n"))
	m++;
	if (!m)
	return;

	path = locate_path(params, _getenv(params, "PATH="), params->argv[0]);
	if (path)
	{
	path = path;
	fork_command(params);
	}
	else
	{
	if ((interactive(params) || _getenv(params, "PATH=")
	|| params->argv[0][0] == '/') && is_command(params, argv[0]))
	fork_command(params);
	else if (*(arg) != '\n')
	{
	params->status = 127;
	perror("command not found\n");
	}

	}
	}
