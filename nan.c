#include "shell.h"

/**
 * is_chain - test current char in buffer delimeter
 * @params: struct the parameter
 * @buf: char the buffer
 * @p: area of position in buf
 *
 * Return: if chain delimeter is 1, otherwise 0
 */
int is_chain(params_t *params, char *buf, size_t *p)
{
	size_t k = *b;

	if (buf[k] == '|' && buf[k + 1] == '|')
	{
		buf[k] = 0;
		k++;
		params->cmd_buf_type = CMD_OR;
	}
	else if (buf[k] == '&' && buf[k + 1] == '&')
	{
		buf[k] = 0;
		k++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[k] == ';') /* found end of this command */
	{
		buf[k] = 0; /* replace semicolon with null */
		params->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*b = k;
	return (1);
}

/**
 * check_chain - check and continue to chain base on status
 * @params: struct the parameter
 * @buf: char the buffer
 * @b: area of buf position
 * @a: start buf position
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(params_t *params, char *buf, size_t *b, size_t a, size_t len)
{
	size_t k = *b;

	if (params->cmd_buf_type == CMD_AND)
	{
		if (params->status)
		{
			buf[a] = 0;
			k = len;
		}
	}
	if (params->cmd_buf_type == CMD_OR)
	{
		if (!params->status)
		{
			buf[a] = 0;
			k = len;
		}
	}

	*b = k;
}

/**
 * replace_alias - replaces aliases string token
 * @params: struct the parameter
 *
 * Return: replaced 1 if, otherwise 0,
 */
int replace_alias(params_t *params)
{
	int a;
	list_t *node;
	char *b;

	for (a = 0; a < 10; a++)
	{
		node = node_starts_with(params->alias, params->argv[0], '=');
		if (!node)
			return (0);
		free(params->argv[0]);
		b = _strchr(node->str, '=');
		if (!b)
			return (0);
		b = _strdup(b + 1);
		if (!b)
			return (0);
		params->argv[0] = b;
	}
	return (1);
}

/**
 * replace_vars - replaces vars to string token
 * @params: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(params_t *params)
{
	int a = 0;
	list_t *node;

	for (a = 0; params->argv[a]; a++)
	{
		if (params->argv[a][0] != '$' || !params->argv[a][1])
			continue;

		if (!_strcmp(info->argv[a], "$?"))
		{
			replace_string((&params->argv[a]),
				_strdup(convert_number(params->status, 10, 0)));
			continue;
		}
		if (!_strcmp(params->argv[a], "$$"))
		{
			replace_string(&(info->argv[a]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &params->argv[a][1], '=');
		if (node)
		{
			replace_string(&(params->argv[a]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&params->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - string replaces
 * @old: old string areas
 * @new: string new
 *
 * Return: if replaced 1,  otherwise 0
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
