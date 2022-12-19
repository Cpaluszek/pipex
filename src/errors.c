/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 09:27:41 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 09:08:16 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Todo: single error command
void	print_sys_error(char *str, int err_code)
{
	perror(str);
	exit(err_code);
}

void	print_error(char *str, int err_code)
{
	ft_printf_fd(STDERR_FILENO, str);
	exit(err_code);
}

// // Error while accessing to a file
// void	file_error(void)
// {
// 	perror("File error");
// 	exit(2);
// }

// // Error while executing a program
// void	program_error(void)
// {
// 	perror("Program error");
// 	exit(3);
// }

// // Error while allocating memory
// void	allocation_error(void)
// {
// 	ft_printf_fd(STDERR_FILENO, "Allocation error\n");
// 	exit(4);
// }

void	env_error(void)
{
	ft_printf_fd(STDERR_FILENO, "Environment Missing\n");
	exit(5);
}
