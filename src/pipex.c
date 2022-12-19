/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 13:22:55 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

int	main(int argc, char **argv, char **env)
{
	t_args	args;
	int		input_fd;

	if (argc != 5)
		print_error_exit(ARG_ERROR);
	input_fd = open(argv[1], O_RDONLY);
	if (input_fd == -1)
		print_perror_exit(FILE_ERROR);
	args.first_cmd = parse_program(argv[2], env);
	args.second_cmd = parse_program(argv[3], env);
	execute_first_program(input_fd, args.first_cmd, env);
	execute_second_program(argv[4], args.first_cmd, env);
}
