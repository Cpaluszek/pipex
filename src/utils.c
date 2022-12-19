/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:39:50 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 16:49:40 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

void	parent_free_and_close(t_pipex *pipex)
{
	if (pipex->paths)
		free_split(pipex->paths);
	if (pipex->first_cmd)
		free_split(pipex->first_cmd);
	if (pipex->second_cmd)
		free_split(pipex->second_cmd);
	if (close(pipex->in_file) == -1)
		print_perror_exit(CLOSE_ERROR);
	if (close(pipex->out_file) == -1)
		print_perror_exit(CLOSE_ERROR);
}
