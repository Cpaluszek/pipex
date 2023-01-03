/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:06:31 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/03 14:38:31 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

// Free an array of strings
void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
	split = NULL;
}

// Close both ends of the generated pipe
void	close_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->pipes_count)
	{
		if (close(pipex->pipes[i]) == -1)
		{
			parent_free(pipex);
			print_perror_exit(CLOSE_ERROR);
		}
		i++;
	}
}

// Free all allocation in t_pipex
// Close input and ouput files
// if 1st param is here_doc unlink() will remove temp file
void	parent_free(t_pipex *pipex)
{
	if (pipex->paths != NULL)
		free_split(pipex->paths);
	if (pipex->pipes != NULL)
		free(pipex->pipes);
	if (pipex->cmd_args != NULL)
		free_split(pipex->cmd_args);
	if (close(pipex->in_file) == -1)
		print_perror_exit(CLOSE_ERROR);
	if (close(pipex->out_file) == -1)
		print_perror_exit(CLOSE_ERROR);
	if (pipex->here_doc)
		unlink(HERE_DOC_TMP_FILE);
}
