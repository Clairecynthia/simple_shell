#include "shell.h"

/**
 * _isexit - Function to exit the shell.
 * @params: Structure containing potential arguments.
 *
 * Return: Exits with the given exit status.
 *         (0) if params->argv[0] != "exit".
 */
	int _isexit(params_t *params)
	{
	int exitcheck;

	if (params->argv[1])  /* If there is an exit argument */
	{
	exitcheck = _erratoi(params->argv[1]);
	if (exitcheck == -1)
	{
	params->status = 2;
	print_error(params, "Illegal number: ");
	_eputs(params->argv[1]);
	_eputchar('\n');
	return (1);
	}
	params->err_num = _erratoi(params->argv[1]);
	return (-2);
	}
	params->err_num = -1;
	return (-2);
	}

/**
 * _iscd - Changes the current directory of the process.
 * @params: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
        int _iscd(params_t *params)
        {
        char *l, *dir, buffer[1024];
        int chdir_ret;

        l = getcwd(buffer, 1024);
        if (!s)
        _puts("TODO: >>getcwd failure emsg here<<\n");
        if (argv[1])
        {
        dir = _getenv(params, "HOME=");
        if (!dir)
        chdir_ret = /* TODO: what should this be? */
        chdir((dir = _getenv(params, "PWD=")) ? dir : "/");
        else
        chdir_ret = chdir(dir);
        }
        else if (_strcmp(argv[1], "-") == 0)
        {
        if (!_getenv(params, "OLDPWD="))
        {
        _puts(l);
        _putchar('\n')
        return (1);
        }
        _puts(_getenv(params, "OLDPWD=")), _putchar('\n');
        chdir_ret = /* TODO: what should this be? */
        chdir((dir = _getenv(params, "OLDPWD=")) ? dir : "/");env(params, "OLDPWD", _getenv(params, "PWD="));
	_setenv(params, "PWD", getcwd(buffer, 1024));
	}
	return (0);
	}

/**
 * _ishelp - Displays a help message.
 * @params: Structure containing potential arguments.
 *
 * Return: Always 0.
 */
	int _ishelp(params_t *params)
	{
	char **arg_array;

	arg_array = argv;
	_puts("Help call works. Function not yet implemented.\n");
	if (0)
	_puts(*arg_array);
	return (0);
	}
