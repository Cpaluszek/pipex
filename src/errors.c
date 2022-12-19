/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 09:27:41 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 11:58:53 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Todo: refacto
void	print_sys_error_exit(char *str, int err_code)
{
	perror(str);
	exit(err_code);
}

void	print_error_exit(char *str, int err_code)
{
	ft_printf_fd(STDERR_FILENO, str);
	exit(err_code);
}
