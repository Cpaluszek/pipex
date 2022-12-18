/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 09:27:41 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/18 10:09:56 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	argument_error(void)
{
	ft_printf_fd(STDERR_FILENO,
		"Invalid parameters:\n./pipex file1 cmd1 cmd2 file2\n");
	exit(1);
}

// Error while accessing to a file
void	file_error(void)
{
	perror("File error");
	exit(2);
}

// Error while executing a program
void	program_error(void)
{
	perror("Program error");
	exit(3);
}

// Error while allocating memory
void	allocation_error(void)
{
	ft_printf_fd(STDERR_FILENO, "Allocation error\n");
	exit(4);
}

