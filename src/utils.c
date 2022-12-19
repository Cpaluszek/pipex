/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:39:50 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 09:33:02 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// Note: too much to include pipex.h?
#include "pipex.h"

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}
