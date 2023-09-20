#include "shell.h"

/**
 * fork_command - Creates a new process to execute a shell command
 * @params: Pointer to the shell information struct
 *
 * Return: This function does not return a value (void).
 */
	void fork_command(params_t, *params)
	{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
	perror("Error:");
	return;
	}
	if (child_pid == 0)
	{
	if (execve(path, argv, get_environ(params)) == -1)
	{
	free_params(params, 1);
	if (errno == EACCES)
	exit(126);
	exit(1);
	}
	}
	else
	{
	wait(&(status));
	if (WIFEXITED(status))
	{
	status = WEXITSTATUS(status);
	if (status == 126)
	print_error(params, "Permission denied\n");
	}
	}
	}
