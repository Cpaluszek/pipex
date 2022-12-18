/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/18 10:54:05 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **env)
{
	int		file1;
	int		exec_ret;
	char	*prog_path;

	if (argc != 5)
		argument_error();
	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
		file_error();

	prog_path = find_program(argv[2], env);
	exec_ret = execve(prog_path, argv + 2, env);
	free(prog_path);
	if (exec_ret == -1)
		program_error();
}
