/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:16:32 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/20 08:59:00 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Note: search about waitpid parameters
// Note: free alls cmd in case of error ?
// Creating a child process using fork to execute the 1st command
void	execute_first_program(t_pipex *pipex)
{
	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		parent_free_and_close(pipex);
		print_perror_exit(FORK_ERROR);
	}	
	if (pipex->pid1 == 0)
	{
		if (dup2(pipex->in_file, STDIN_FILENO) == -1)
			print_perror_exit(DUP2_ERROR);
		if (close(pipex->in_file) == -1 | close(pipex->pipe[0]) == -1)
			print_perror_exit(CLOSE_ERROR);
		if (dup2(pipex->pipe[1], STDOUT_FILENO) == -1)
			print_perror_exit(DUP2_ERROR);
		if (execve(pipex->first_cmd[0], pipex->first_cmd, pipex->env) == -1)
			print_perror_exit(pipex->first_cmd[0]);
	}
}

// Creating a child process using fork to execute the 2nd command
void	execute_second_program(t_pipex *pipex)
{
	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		parent_free_and_close(pipex);
		print_perror_exit(FORK_ERROR);
	}
	if (pipex->pid2 == 0)
	{
		if (dup2(pipex->pipe[0], STDIN_FILENO) == -1)
			print_perror_exit(DUP2_ERROR);
		if (close(pipex->pipe[1]) == -1)
			print_perror_exit(CLOSE_ERROR);
		if (dup2(pipex->out_file, STDOUT_FILENO) == -1)
			print_perror_exit(PIPE_ERROR);
		if (execve(pipex->second_cmd[0], pipex->second_cmd, pipex->env) == -1)
			print_perror_exit(pipex->second_cmd[0]);
	}
}
