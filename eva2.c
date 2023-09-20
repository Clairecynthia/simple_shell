#include "shell.h"

/**
* get_environ -  The string array should be returned
* @params: Structure carries arguments. maintain
*           prototype func
* Return: 0 Always.
*/
char **get_environ(params_t *params)
{
if (!params->envi || params->env_changed)
{
params->envi = list_to_strings(params->env);
params->env_changed = 0;
}

return (params->environ);
}

/**
* _unsetenv - Remove variable environment
* @params: Structure carries arguments. maintain
*         prototype func
*  Return: delete 1, otherwise 0
* @var: env var to string
*/
int _unsetenv(params_t *params, char *var)
{
list_t *node = params->env;
size_t a = 0;
char *b;

if (!node || !var)
return (0);

while (node)
{
b = starts_with(node->str, var);
if (b && *b == '=')
{
params->env_changed = delete_node_at_index(&(params->env), a);
a = 0;
node = params->env;
continue;
}
node = node->next;
a++;
}
return (params->env_changed);
}

/**
* _setenv - create another new variable envi,
*             or edit an existing variable
* @params: Structure carries arguments.maintain
*         prototype func.
* @var:  var envi to string
* @value: var env to string
*  Return: 0 Always.
*/
int _setenv(params_t *params, char *var, char *value)
{
char *buf = NULL;
list_t *node;
char *b;

if (!var || !value)
return (0);

buf = malloc(_strlen(var) + _strlen(value) + 2);
if (!buf)
return (1);
_strcpy(buf, var);
_strcat(buf, "=");
_strcat(buf, value);
node = params->env;
while (node)
{
b = starts_with(node->str, var);
if (b && *b == '=')
{
free(node->str);
node->str = buf;
params->env_changed = 1;
return (0);
}
node = node->next;
}
add_node_end(&(params->env), buf, 0);
free(buf);
params->env_changed = 1;
return (0);
}
