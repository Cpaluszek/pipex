/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:09:05 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/04 10:12:18 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>

// Print error message from errno and exit program
void	print_perror_exit(char *str)
{
	perror(str);
	exit(1);
}

// Print error message from errno
void	print_perror(char *str)
{
	perror(str);
}

// Print custom error merssage when the program can't access file
// Then exit the program
void	file_error_exit(char *str)
{
	ft_printf_fd(STDERR_FILENO, "%s: %s\n", strerror(errno), str);
	exit(1);
}

// Print custom error message and exit program
void	print_error_exit(char *str)
{
	ft_printf_fd(STDERR_FILENO, str);
	exit(1);
}
