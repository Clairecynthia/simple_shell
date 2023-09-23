#include "shell.h"

/**
 * _iseva - prints the eva that is currently esxisting
 * @params: The structure which carries argument. maintain
 *           prototype constant.
 * Return: 0 Always.
 */
int _iseva(params_t *params)
{
	print_list_str(params->eva);
	return (0);
}

/**
 * _geteva - gets value to a variable eva
 * @params: The structure which carries argument. maintain
 * @name: name of variable environment
 *
 * Return: value
 */
char *_geteva(params_t *params, const char *name)
{
	list_t *node = params->eva;
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
 * _isseteva -create another eva variable,
 *             or edit an already existing variable
 * @params: Structure carries arguments.  maintain
 *          prototype to constant
 *  Return: 0 Always.
 */
int _isseteva(params_t *params)
{
	if (params->argc != 3)
	{
		_eputs("Incorrect numb of arguements\n");
		return (1);
	}
	if (_seteva(params, params->argv[1], params->argv[2]))
		return (0);
	return (1);
}

/**
 * _isunsetenv - Remove a variable envi
 * @params: Structure carries argument. maintain
 *      prototype func
 *  Return: Always 0
 */
int _isunsetenvi(params_t *params)
{
	int a;

	if (params->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		_unseteva(params, params->argv[a]);

	return (0);
}

/**
 * populate_env_list - populates eva linked list
 * @params: Structure carries arguments. maintain
 *           prototype func.
 * Return: Always 0
 */
int populate_environ_list(params_t *params)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; eva[a]; a++)
		add_node_end(&node, environ[a], 0);
	params->env = node;
	return (0);
}
