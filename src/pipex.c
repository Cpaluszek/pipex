/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/05 15:25:52 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	get_cmds(t_pipex *pipex, char **argv);

int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc != 5)
		print_error_exit(ARG_ERROR);
	open_files(&pipex, argv[1], argv[4]);
	pipex.env = env;
	pipex.paths = get_paths(env, argv[2], argv[3]);
	if (pipe(pipex.pipe) == -1)
	{
		free_split(pipex.paths);
		print_perror_exit(PIPE_ERROR);
	}
	get_cmds(&pipex, argv);
	execute_first_program(&pipex, argv[1]);
	execute_second_program(&pipex, argv[4]);
	close_pipes(&pipex);
	waitpid(pipex.pid1, NULL, 0);
	waitpid(pipex.pid2, NULL, 0);
	parent_free(&pipex);
	return (0);
}

// Search for program access
// Use PATH in env if no absolute path
static void	get_cmds(t_pipex *pipex, char **argv)
{
	pipex->first_cmd = parse_program(argv[2], pipex);
	pipex->second_cmd = parse_program(argv[3], pipex);
}
