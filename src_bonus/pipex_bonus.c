/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/03 11:38:44 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

static void	create_pipes(t_pipex *pipex);

// Note: why -1 on wait
// Todo: check all includes -> only bonuses
int	main(int argc, char **argv, char **env)
{
	t_pipex	pipex;

	if (argc < count_args(argv[1], &pipex))
		print_error_exit(ARG_ERROR);
	pipex.env = env;
	pipex.paths = get_paths(env);
	if (pipex.paths == NULL)
		print_perror_exit(ALLOC_ERROR);
	get_input_file(argv, &pipex);
	get_output_file(argv[argc - 1], &pipex);
	pipex.cmd_count = argc - 3 - pipex.here_doc;
	pipex.pipes_count = 2 * (pipex.cmd_count - 1);
	create_pipes(&pipex);
	pipex.child_id = 0;
	while (pipex.child_id < pipex.cmd_count)
	{
		child(&pipex, argv);
		pipex.child_id++;
	}
	close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	parent_free(&pipex);
	return (0);
}

// Create pipes (command count - 1)
static void	create_pipes(t_pipex *pipex)
{
	int	i;

	pipex->pipes = malloc(sizeof(int) * pipex->pipes_count);
	if (pipex->pipes == NULL)
	{
		parent_free(pipex);
		print_perror_exit(ALLOC_ERROR);
	}
	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->pipes + (2 * i)) == -1)
		{
			// Should close previous pipes ?
			parent_free(pipex);
			print_perror_exit(PIPE_ERROR);
		}
		i++;
	}
}
