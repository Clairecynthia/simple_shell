#include "shell.h"

/**
 * _myenv - prints the envi that is currently esxisting
 * @params: The structure which carries argument. maintain
 *           prototype constant.
 * Return: 0 Always.
 */
int _myenv(params_t *params)
{
	print_list_str(params->env);
	return (0);
}

/**
 * _getenv - gets value to a variable envi
 * @params: The structure which carries argument. maintain
 * @name: name of variable environment
 *
 * Return: value
 */
char *_getenv(params_t *params, const char *name)
{
	list_t *node = params->env;
	char *b;

	while (node)
	{
		b = starts_with(node->str, name);
		if (b && *b)
			return (b);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv -create another envi variable,
 *             or edit an already existing variable
 * @params: Structure carries arguments.  maintain
 *          prototype to constant
 *  Return: 0 Always.
 */
int _mysetenv(params_t *params)
{
	if (params->argc != 3)
	{
		_eputs("Incorrect numb of arguements\n");
		return (1);
	}
	if (_setenv(params, params->argv[1], params->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove a variable envi
 * @params: Structure carries argument. maintain
 *      prototype func
 *  Return: Always 0
 */
int _myunsetenv(params_t *params)
{
	int a;

	if (params->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		_unsetenv(params, params->argv[a]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @params: Structure carries arguments. maintain
 *           prototype func.
 * Return: Always 0
 */
int populate_env_list(params_t *params)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	params->env = node;
	return (0);
}
