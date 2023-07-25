#include "main.h"

/**
 * built_in_handler - determines whether the command is built in or not
 * @builtin: command
 * Return: 0
 */
int built_in_handler(char **builtin)
{
	int builtIntSize = 5;
	int i;

	built_in check_built[] = {
			{"cd", _cd},
			{"env", _env},
			{"setenv", _setenv},
			{"unsetenv", _unsetenv},
			{"exit", _exit_}
	};

	for (i = 0; i < builtIntSize; i++)
	{
		if (_strcmp(check_built[i].name, builtin[0]) == 0)
		{
			check_built[i].func(builtin);
			return (1);
		}
	}
	return (0);
}

/**
 * execute - function to execute the commands
 * @command: the command that should be executed
 * @envp: array of environments
 */
void execute(char **command, char *envp[])
{
	char *actual_command = command[0];
	char *command_path = NULL;
	pid_t child = 0;
	int status, check_build;

	check_build = built_in_handler(command);
	if (!check_build)
	{
		command_path = _which(actual_command);
		if (command_path)
		{
			actual_command = command_path;
			child = fork();
		}
		if (child < 0)
		{
			perror("Error");
			exit(errno);
		}
		else if (child == 0)
		{
			if (access(actual_command, R_OK) != 0)
			{
				_perror(actual_command, ": not found\n");
				exit_status = 127;
				return;
			}
			if (execve(actual_command, command, envp) == -1)
				perror("Error");
		}
		else
			wait(&status);
	}
	free(command_path);
}

/**
 * _which - looks for files in the current PATH.
 * @file_name: file name
 *
 * Return: file path
 */
char *_which(char *file_name)
{
	char cwd[256];
	char *dir_path;
	char *c_w_d;
	char *c_w_d_temp;
	list_path *path_directories, *head;
	struct stat st;
	int i = 0;

	path_directories = list_path_directory();
	head = path_directories;
	getcwd(cwd, sizeof(cwd));

	if (stat(file_name, &st) == 0)
	{
		free_list(head);
		return (_strdup(file_name));
	}

	while (path_directories != NULL)
	{
		dir_path = path_directories[i].dir;
		chdir(dir_path);
		if (stat(file_name, &st) == 0)
		{
			c_w_d_temp = dir_path;
			c_w_d = str_concat(c_w_d_temp, "/");
			c_w_d_temp = str_concat(c_w_d, file_name);
			free(c_w_d);
			chdir(cwd);
			free_list(head);
			return (c_w_d_temp);
		}
		path_directories = path_directories->next_node;
	}
	chdir(cwd);
	free_list(head);
	return (NULL);
}
