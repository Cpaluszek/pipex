/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:16:32 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 12:56:06 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Creating a child process to execute a program
// Note: search about waitpid parameters
		// Todo: Protect dup
		// Todo: Protect close
void	execute_program(int input_fd, char **prog_with_args, char **env)
{
	int	pid;
	int	exec_ret;

	pid = fork();
	if (pid == -1)
	{
		free_split(prog_with_args);
		print_sys_error_exit(FORK_ERROR, 1);	
	}	
	if (pid == 0)
	{
		dup2(input_fd, STDIN_FILENO);
		if (close(input_fd))
			print_sys_error_exit(CLOSE_ERROR, 1);
		printf("Child process start\n");
		exec_ret = execve(prog_with_args[0], prog_with_args, env);
		if (exec_ret == -1)
			print_sys_error_exit("Execution error", 1);
	}
	else
	{
		printf("Parent process\n");
		waitpid(pid, NULL, 0);
		free_split(prog_with_args);
	}
}
