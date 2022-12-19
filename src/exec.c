/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:16:32 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 13:23:25 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Creating a child process to execute a program
// Note: search about waitpid parameters
void	execute_first_program(int input_fd, char **prog_with_args, char **env)
{
	pid_t	pid;
	int		exec_ret;
	int		new_fd;

	pid = fork();
	if (pid == -1)
	{
		free_split(prog_with_args);
		print_perror_exit(FORK_ERROR);
	}	
	if (pid == 0)
	{
		new_fd = dup2(input_fd, STDIN_FILENO);
		if (new_fd == -1)
			print_perror_exit(DUP2_ERROR);
		if (close(input_fd))
			print_perror_exit(CLOSE_ERROR);
		exec_ret = execve(prog_with_args[0], prog_with_args, env);
		if (exec_ret == -1)
			print_perror_exit(EXEC_ERROR);
	}
	waitpid(pid, NULL, 0);
	free_split(prog_with_args);
}

void	execute_second_program(char *output, char **prog_with_args, char **env)
{
	int	out_fd;

	(void) prog_with_args;
	(void) env;
	out_fd = open(output, O_CREAT | O_TRUNC | O_RDWR);
	if (out_fd == -1)
		print_perror_exit(FILE_ERROR);
}
