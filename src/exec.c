/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 15:16:32 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/04 12:50:26 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Creating a child process using fork to execute the 1st command
void	execute_first_program(t_pipex *pipex, char *input)
{
	int	exec_err;

	pipex->pid1 = fork();
	if (pipex->pid1 == -1)
	{
		parent_free(pipex);
		print_perror_exit(FORK_ERROR);
	}
	if (pipex->pid1 == 0)
	{
		if (pipex->in_file == -1)
		{
			close_pipes(pipex);
			file_error_exit(input);
		}
		if (dup2(pipex->in_file, STDIN_FILENO) == -1)
			print_perror_exit(DUP2_ERROR);
		if (close(pipex->in_file) == -1 | close(pipex->pipe[0]) == -1)
			print_perror_exit(CLOSE_ERROR);
		if (dup2(pipex->pipe[1], STDOUT_FILENO) == -1)
			print_perror_exit(DUP2_ERROR);
		exec_err = execve(pipex->first_cmd[0], pipex->first_cmd, pipex->env);
		if (exec_err == -1)
			print_perror_exit(EXEC_ERROR);
	}
}

// Creating a child process using fork to execute the 2nd command
void	execute_second_program(t_pipex *pipex, char *output)
{
	int	exec_err;

	pipex->pid2 = fork();
	if (pipex->pid2 == -1)
	{
		parent_free(pipex);
		print_perror_exit(FORK_ERROR);
	}
	if (pipex->pid2 == 0)
	{
		if (pipex->out_file == -1)
		{
			close_pipes(pipex);
			file_error_exit(output);
		}
		if (dup2(pipex->pipe[0], STDIN_FILENO) == -1)
			print_perror_exit(DUP2_ERROR);
		if (close(pipex->pipe[1]) == -1)
			print_perror_exit(CLOSE_ERROR);
		if (dup2(pipex->out_file, STDOUT_FILENO) == -1)
			print_perror_exit(PIPE_ERROR);
		exec_err = execve(pipex->second_cmd[0], pipex->second_cmd, pipex->env);
		if (exec_err == -1)
			print_perror_exit(EXEC_ERROR);
	}
}
