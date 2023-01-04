/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:29:22 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/04 15:19:30 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	dup_fds(int reading_end, int writing_end);
static void	get_cmd(char *arg, t_pipex *pipex);

// Create a child process using fork to execute command
void	child(t_pipex *pipex, char **argv, int argc)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		close_pipes(pipex);
		parent_free(pipex);
		print_perror_exit(FORK_ERROR);
	}
	if (pipex->pid == 0)
	{
		if (pipex->child_id == 0)
		{
			if (pipex->in_file == -1)
			{
				close_pipes(pipex);
				if (pipex->here_doc)
				{
					if (unlink(HERE_DOC_TMP_FILE) == -1)
						print_perror(UNLINK_ERROR);
					print_perror_exit(FILE_ERROR);
				}
				file_error_exit(argv[1]);
			}
			dup_fds(pipex->in_file, pipex->pipes[1]);
		}
		else if (pipex->child_id == pipex->cmd_count - 1)
		{
			if (pipex->out_file == -1)
			{
				close_pipes(pipex);
				file_error_exit(argv[argc - 1]);
			}
			dup_fds(pipex->pipes[2 * pipex->child_id - 2], pipex->out_file);
		}
		else
			dup_fds(pipex->pipes[2 * pipex->child_id - 2],
				pipex->pipes[2 * pipex->child_id + 1]);
		close_pipes(pipex);
		get_cmd(argv[2 + pipex->here_doc + pipex->child_id], pipex);
		if (execve(pipex->cmd_args[0], pipex->cmd_args, pipex->env) == -1)
		{
			free_split(pipex->cmd_args);
			print_perror_exit(EXEC_ERROR);
		}
	}
}

// Parse input parameters to find the command to execute
static void	get_cmd(char *arg, t_pipex *pipex)
{
	pipex->cmd_args = parse_program(arg, pipex);
	if (pipex->cmd_args[0] == NULL)
	{
		free_split(pipex->paths);
		free_split(pipex->cmd_args);
		exit(127);
	}
}

// Duplicate STDIN and STDOUT to the desired fds
static void	dup_fds(int reading_end, int writing_end)
{
	if (dup2(reading_end, STDIN_FILENO) == -1)
		print_perror_exit(DUP2_ERROR);
	if (dup2(writing_end, STDOUT_FILENO) == -1)
		print_perror_exit(DUP2_ERROR);
}
