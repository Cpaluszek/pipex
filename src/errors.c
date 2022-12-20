/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 09:27:41 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/20 08:58:28 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <string.h>

// Print error message from errno and exit program
void	print_perror_exit(char *str)
{
	perror(str);
	exit(1);
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
