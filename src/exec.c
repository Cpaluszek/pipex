/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:16:32 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/18 15:16:48 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Creating a child process to execute a program
// Note: search about waitpid parameters
void	execute_program(int input_fd, char **prog_with_args, char **env)
{
	int	pid;
	int	exec_ret;

	pid = fork();
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
		printf("Child process start\n");
		exec_ret = execve(prog_with_args[0], prog_with_args, env);
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
