/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:39:50 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 17:28:57 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i] != NULL)
		free(split[i++]);
	free(split);
}

void	close_pipes(t_pipex *pipex)
{
	if (close(pipex->pipe[0]) == -1)
		print_perror_exit(CLOSE_ERROR);
	if (close(pipex->pipe[1]) == -1)
		print_perror_exit(CLOSE_ERROR);
}

void	parent_free_and_close(t_pipex *pipex)
{
	if (pipex->paths != NULL)
		free_split(pipex->paths);
	if (pipex->first_cmd != NULL)
		free_split(pipex->first_cmd);
	if (pipex->second_cmd != NULL)
		free_split(pipex->second_cmd);
	if (close(pipex->in_file) == -1)
		print_perror_exit(CLOSE_ERROR);
	if (close(pipex->out_file) == -1)
		print_perror_exit(CLOSE_ERROR);
}
