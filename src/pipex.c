/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 16:49:36 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdlib.h>

static void	close_pipes(t_pipex *pipex);

// Todo: split paths 2 time not optimal
// add paths var in pipex struct
int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		print_error_exit(ARG_ERROR);
	pipex.in_file = open(argv[1], O_RDONLY);
	if (pipex.in_file == -1)
		print_perror_exit(FILE_ERROR);
	pipex.out_file = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pipex.out_file == -1)
		print_perror_exit(FILE_ERROR);
	pipex.env = env;
	pipex.paths = get_paths(env);
	if (pipex.paths == NULL)
		print_perror_exit(ALLOC_ERROR);
	if (pipe(pipex.pipe) == -1)
		print_perror_exit(PIPE_ERROR);
	pipex.first_cmd = parse_program(argv[2], &pipex);
	pipex.second_cmd = parse_program(argv[3], &pipex);
	execute_first_program(&pipex);
	execute_second_program(&pipex);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free_and_close(&pipex);
}

static void	close_pipes(t_pipex *pipex)
{
	if (close(pipex->pipe[0]) == -1)
		print_perror_exit(CLOSE_ERROR);
	if (close(pipex->pipe[1]) == -1)
		print_perror_exit(CLOSE_ERROR);
}
