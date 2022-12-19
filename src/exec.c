/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:16:32 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 10:40:40 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Creating a child process to execute a program
// Note: search about waitpid parameters
void	execute_program(int input_fd, char **prog_with_args, char **env)
{
	int	pid;
	int	exec_ret;

	// Todo: check fork return -1 -> exit
	pid = fork();
	if (pid == 0)
	{
		// Todo: Protect dup
		dup2(input_fd, STDIN_FILENO);
		// Todo: Protect close
		close(input_fd);
		printf("Child process start\n");
		exec_ret = execve(prog_with_args[0], prog_with_args, env);
		if (exec_ret == -1)
			print_sys_error_exit("Execution error", 3);
	}
	else
	{
		printf("Parent process\n");
		waitpid(pid, NULL, 0);
		free_split(prog_with_args);
	}
}
