/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:29:22 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/02 10:17:02 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	dup_fds(int reading_end, int writing_end);
static void	get_cmd(char *arg, t_pipex *pipex);

void	child(t_pipex *pipex, char **argv)
{
	pipex->pid = fork();
	if (pipex->pid == -1)
	{
		parent_free(pipex);
		print_perror_exit(FORK_ERROR);
	}
	if (pipex->pid == 0)
		dup_fds(pipex->in_file, pipex->pipes[1]);
	else if (pipex->pid == pipex->cmd_count - 1)
		dup_fds(pipex->pipes[2 * pipex->child_id - 2], pipex->out_file);
	else
		dup_fds(pipex->pipes[2 * pipex->child_id - 2],
			pipex->pipes[2 * pipex->child_id + 1]);
	close_pipes(pipex);
	get_cmd(argv[2 + pipex->here_doc + pipex->child_id], pipex);
	execve(pipex->cmd_args[0], pipex->cmd_args, pipex->env);
}

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

static void	dup_fds(int reading_end, int writing_end)
{
	if (dup2(reading_end, STDIN_FILENO) == -1)
		print_perror_exit(DUP2_ERROR);
	if (dup2(writing_end, STDOUT_FILENO) == -1)
		print_perror_exit(DUP2_ERROR);
}
