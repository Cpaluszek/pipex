/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 09:11:24 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

// Todo: free_split in libft
int	main(int argc, char **argv, char **env)
{
	int		input_fd;
	char	**command_with_args;
	char	*input_file_path;
	char	*first_command;

	input_file_path = argv[1];
	first_command = argv[2];
	if (argc != 5)
		print_error(ARG_ERROR, 1);
	input_fd = open(input_file_path, O_RDONLY);
	if (input_fd == -1)
		print_sys_error(FILE_ERROR, 2);
	command_with_args = parse_program(first_command, env);
	execute_program(input_fd, command_with_args, env);
	printf("Parent process exit\n");
}
