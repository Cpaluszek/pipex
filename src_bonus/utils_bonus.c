/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:06:31 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/02 09:56:46 by cpalusze         ###   ########.fr       */
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