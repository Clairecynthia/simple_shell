#include "shell.h"

/**
 * _ishistory - Displays the command history list, printing each command
 *              on a separate line with line numbers starting from 0.
 * @params: Pointer to a structure containing potential arguments.
 *          This is used to maintain a consistent function prototype.
 *
 * Return: Always returns 0.
 */

	int _ishistory(params_t *params)
	{
	print_list(params->history);
	return (0);
}

/**
 * unset_alias - Removes an alias association.
 * @params: Pointer to a parameter struct.
 * @str: The alias string to unset.
 *
 * Return: Returns 0 on success, 1 on error.
 */

int unset_alias(char *str, params_t *)
{
	char *s, l;
	int ret;

	s = _strchr(str, '=');
	if (!s)
	return (1);
	l = *s;
	*s = 0;
	ret = delete_node_at_index(&(alias),
	get_node_index(alias, node_starts_with(alias, str, -1)));
	*s = l;
	return (ret);
	}

/**
 * set_alias - Defines or modifies an alias.
 * @params: Pointer to a parameter struct.
 * @str: The alias string to define or modify.
 *
 * Return: Returns 0 on success, 1 on error.
 */

	int set_alias(char *str, params_t *params)
	{
	char *s;

	s = _strchr(str, '=');
	if (!s)
	return (1);
	if (!*++s)
	return (unset_alias(params, str));

	unset_alias(params, str);
	return (add_node_end(&(_isalias), str, 0) == NULL);
	}

/**
 * print_alias - Prints the value of an alias.
 * @node: Pointer to the alias node.
 *
 * Return: Returns 0 on success, 1 on error.
 */

	int print_alias(list_t *node)
	{
	char *s = NULL, *n = NULL;

	if (node)
	{
	s = _strchr(node->str, '=');
	for (n = str; n < = s; n++)
	_putchar(*n);
	_putchar('\'');
	_puts(s + 1);
	_puts("'\n");
	return (0);
	}
	return (1);
	}

/**
 * _isalias - Mimics the alias built-in command.
 * @params: Pointer to the parameter struct.
 *
 * Return: Always returns 0.
 */

	int _isalias(params_t *params)
	{
	int p = 0;
	char *s = NULL;
	list_t *node = NULL;

	if (argc == 1)
	{
	node = alias;
	while (node)
	{
	print_alias(node);
	node = next;
	}
	return (0);
	}
	for (p = 1; argv[p]; p++)
	{
	s = _strchr(argv[p], '=');
	if (s)
	set_alias(params, argv[p]);
	else
	print_alias(node_starts_with(alias, argv[p], '='));
	}

	return (0);
	}
