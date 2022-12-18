/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/18 13:25:24 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

// Todo: free_split in libft

void	execute_program(char **prog_with_args, char **env);

int	main(int argc, char **argv, char **env)
{
	int		input_fd;
	char	**command_with_args;
	char	*input_file_path;
	char	*first_command;

	input_file_path = argv[1];
	first_command = argv[2];
	if (argc != 5)
		argument_error();
	input_fd = open(input_file_path, O_RDONLY);
	if (input_fd == -1)
		file_error();
	command_with_args = parse_program(first_command, env);
	execute_program(command_with_args, env);
	printf("Parent process exit\n");
}

// Creating a child process to execute a program
// Note: search about waitpid parameters
void	execute_program(char **prog_with_args, char **env)
{
	int	pid;
	int	exec_ret;

	pid = fork();
	if (pid == 0)
	{
		printf("Child process start\n");
		exec_ret = execve(prog_with_args[0], prog_with_args + 1, env);
		if (exec_ret == -1)
			program_error();
	}
	else
	{
		printf("Parent process\n");
		waitpid(pid, NULL, 0);
		free_split(prog_with_args);
	}
}
