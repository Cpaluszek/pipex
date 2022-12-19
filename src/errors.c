/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 09:27:41 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 17:54:25 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <errno.h>
#include <string.h>

void	print_perror_exit(char *str)
{
	perror(str);
	exit(1);
}

void	file_error_exit(char *str)
{
	ft_printf_fd(STDERR_FILENO, "%s: %s\n", strerror(errno), str);
	exit(1);
}

void	print_error_exit(char *str)
{
	ft_printf_fd(STDERR_FILENO, str);
	exit(1);
}
