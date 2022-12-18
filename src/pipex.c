/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/18 11:34:44 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

void	execute_program(char *prog_path, char **env);

int	main(int argc, char **argv, char **env)
{
	int		file1;
	char	*prog_path;

	if (argc != 5)
		argument_error();
	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
		file_error();
	prog_path = find_program(argv[2], env);
	execute_program(prog_path, env);
	free(prog_path);
	printf("Parent process exit\n");
}

// Creating a child process to execute a program
// Note: search about waitpid parameters
void	execute_program(char *prog_path, char **env)
{
	int	pid;
	int	exec_ret;

	pid = fork();
	if (pid == 0)
	{
		printf("Child process\n");
		exec_ret = execve(prog_path, NULL, env);
		if (exec_ret == -1)
			program_error();
	}
	else
	{
		printf("Parent process\n");
		waitpid(pid, NULL, 0);
	}
}
