/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/20 11:02:02 by cpalusze         ###   ########.fr       */
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
	get_input_file(argv, &pipex);
	get_output_file(argv[argc - 1], &pipex);
	pipex.cmd_count = argc - 3 - pipex.here_doc;
	pipex.pipes_count = 2 * (pipex.cmd_count - 1);
	pipex.pipes = malloc (sizeof(int) * pipex.pipes_count);
	if (pipex.pipes == NULL)
		print_perror_exit(ALLOC_ERROR);
	pipex.env = env;
	pipex.paths = get_paths(env);
	if (pipex.paths == NULL)
	{
		free(pipex.pipes);
		print_perror_exit(ALLOC_ERROR);
	}
	create_pipes(&pipex);
	pipex.child_id = -1;
	while (pipex.child_id < pipex.cmd_count)
		child(&pipex, argv);
	close_pipes(&pipex);
	waitpid(-1, NULL, 0);
	parent_free_and_close(&pipex);
}

static void	create_pipes(t_pipex *pipex)
{
	int	i;

	i = 0;
	while (i < pipex->cmd_count - 1)
	{
		if (pipe(pipex->pipes + (2 * i)) == -1)
			parent_free_and_close(pipex);	
		i++;
	}
}
