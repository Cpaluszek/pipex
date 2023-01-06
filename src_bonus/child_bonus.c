/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:29:22 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/06 12:49:00 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	manage_first_child(t_pipex *pipex, char *input);
static void	fork_error(t_pipex *pipex);
static void	dup_fds(t_pipex *pipex, int reading_end, int writing_end);
static void	get_cmd(char *arg, t_pipex *pipex);

// Create a child process using fork to execute command
void	child(t_pipex *pip, char **argv, int argc)
{
	pip->pid = fork();
	if (pip->pid == -1)
		fork_error(pip);
	if (pip->pid != 0)
		return ;
	if (pip->child_id == 0)
		manage_first_child(pip, argv[1]);
	else if (pip->child_id == pip->cmd_count - 1)
	{
		if (pip->out_file == -1)
		{
			close_pipes(pip);
			file_error_exit(argv[argc - 1]);
		}
		dup_fds(pip, pip->pipes[2 * pip->child_id - 2], pip->out_file);
	}
	else
		dup_fds(pip, pip->pipes[2 * pip->child_id - 2],
			pip->pipes[2 * pip->child_id + 1]);
	close_pipes(pip);
	get_cmd(argv[2 + pip->here_doc + pip->child_id], pip);
	execve(pip->cmd_args[0], pip->cmd_args, pip->env);
	ft_free_split(pip->cmd_args);
	print_perror_exit(EXEC_ERROR);
}

static void	manage_first_child(t_pipex *pipex, char *input)
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
		file_error_exit(input);
	}
	dup_fds(pipex, pipex->in_file, pipex->pipes[1]);
}

static void	fork_error(t_pipex *pipex)
{
	close_pipes(pipex);
	parent_free(pipex);
	print_perror_exit(FORK_ERROR);
}

// Duplicate STDIN and STDOUT to the desired fds
static void	dup_fds(t_pipex *pipex, int reading_end, int writing_end)
{
	if (dup2(reading_end, STDIN_FILENO) == -1)
	{
		close_pipes(pipex);
		print_perror_exit(DUP2_ERROR);
	}
	if (dup2(writing_end, STDOUT_FILENO) == -1)
	{
		close_pipes(pipex);
		print_perror_exit(DUP2_ERROR);
	}
}

// Parse input parameters to find the command to execute
static void	get_cmd(char *arg, t_pipex *pipex)
{
	pipex->cmd_args = parse_program(arg, pipex);
	if (pipex->cmd_args[0] == NULL)
	{
		ft_free_split(pipex->paths);
		ft_free_split(pipex->cmd_args);
		exit(127);
	}
}
