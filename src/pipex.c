/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/20 08:56:15 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_cmds(t_pipex *pipex, char **argv);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		print_error_exit(ARG_ERROR);
	pipex.in_file = open(argv[1], O_RDONLY);
	if (pipex.in_file == -1)
		file_error_exit(argv[1]);
	pipex.out_file = open(argv[4], O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pipex.out_file == -1)
		print_perror_exit(FILE_ERROR);
	pipex.env = env;
	pipex.paths = get_paths(env);
	if (pipex.paths == NULL)
		print_perror_exit(ALLOC_ERROR);
	if (pipe(pipex.pipe) == -1)
		print_perror_exit(PIPE_ERROR);
	get_cmds(&pipex, argv);
	execute_first_program(&pipex);
	execute_second_program(&pipex);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free_and_close(&pipex);
}

// Search for program access
// Use PATH in env if no absolute path
static void	get_cmds(t_pipex *pipex, char **argv)
{
	pipex->first_cmd = parse_program(argv[2], pipex);
	if (pipex->first_cmd[0] == NULL)
	{
		free_split(pipex->paths);
		free_split(pipex->first_cmd);
		exit(127);
	}
	pipex->second_cmd = parse_program(argv[3], pipex);
	if (pipex->second_cmd[0] == NULL)
	{
		free_split(pipex->paths);
		free_split(pipex->first_cmd);
		exit(127);
	}
}
