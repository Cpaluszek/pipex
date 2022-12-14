/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/14 12:52:36 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <unistd.h>

// Note: print on stderr ?
int	main(int argc, char **argv)
{
	(void) argv;
	if (argc != 5)
	{
		ft_printf_fd(STDERR_FILENO, "Usage: file1 cmd1 cmd2 file2\n");
		return (1);
	}
}
