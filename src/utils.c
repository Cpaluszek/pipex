/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:39:50 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/06 12:48:00 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Close both ends of the generated pipe
void	close_pipes(t_pipex *pipex)
{
	if (close(pipex->pipe[0]) == -1 | close(pipex->pipe[1]) == -1)
	{
		parent_free(pipex);
		print_perror_exit(CLOSE_ERROR);
	}
}

// Free all allocation in t_pipex
void	parent_free(t_pipex *pipex)
{
	if (pipex->paths != NULL)
		ft_free_split(pipex->paths);
	if (pipex->first_cmd != NULL)
		ft_free_split(pipex->first_cmd);
	if (pipex->second_cmd != NULL)
		ft_free_split(pipex->second_cmd);
	if (pipex->in_file != -1 && close(pipex->in_file) == -1)
		print_perror_exit(CLOSE_ERROR);
	if (pipex->out_file != -1 && close(pipex->out_file) == -1)
		print_perror_exit(CLOSE_ERROR);
}
