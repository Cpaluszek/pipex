/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:06:31 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/20 11:01:10 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>

// Todo: move to files_bonus.c ?
void	get_input_file(char **argv, t_pipex *pipex)
{
	if (pipex->here_doc)
		here_doc(argv[2], pipex);
	else
	{
		pipex->in_file = open(argv[1], O_RDONLY);
		if (pipex->in_file == -1)
			file_error_exit(argv[1]);
	}
}

void	get_output_file(char *output_file, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->out_file = open(output_file, O_CREAT | O_APPEND | O_RDWR, 0644);
	else
		pipex->out_file = open(output_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pipex->out_file == -1)
		print_perror_exit(FILE_ERROR);
}

// Free an array of strings
void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
}

// Close both ends of the generated pipe
// Note: to rework, currently free half of the pipes
// Todo: free parent
void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (close(pipex->pipes[i]) == -1)
			print_perror_exit(CLOSE_ERROR);
	}
}

// Todo: adapt function to bonus
// Free all allocation in t_pipex then exit the program
void	parent_free_and_close(t_pipex *pipex)
{
	if (pipex->paths != NULL)
		free_split(pipex->paths);
	if (pipex->cmd_args != NULL)
		free_split(pipex->cmd_args);
	if (close(pipex->in_file) == -1)
		print_perror_exit(CLOSE_ERROR);
	if (close(pipex->out_file) == -1)
		print_perror_exit(CLOSE_ERROR);
}