/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 09:27:41 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/18 09:30:15 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	argument_error(void)
{
	ft_printf_fd(STDERR_FILENO,
		"Invalid parameters:\n./pipex file1 cmd1 cmd2 file2\n");
	exit(1);
}

void	file_error(void)
{
	perror("Error");
	exit(2);
}
