/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:56:27 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/04 10:17:40 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>

static void	check_files(t_pipex *pipex, char *input_file, char *output_file);

// Todo: test avec write permission only on output file
// Open input file, or manage here_doc
// Open or create the output file with truncation
// If 1st param is here_doc append to the output file instead of truncate
void	get_files(char **argv, char *output_file, t_pipex *pipex)
{
	if (pipex->here_doc)
	{
		here_doc(argv[2]);
		pipex->in_file = open(HERE_DOC_TMP_FILE, O_RDONLY);
		pipex->out_file = open(output_file, O_CREAT | O_APPEND | O_RDWR, 0644);
	}
	else
	{
		pipex->in_file = open(argv[1], O_RDONLY);
		pipex->out_file = open(output_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	}
	check_files(pipex, argv[1], output_file);
}

// Check file descriptors for input and output
static void	check_files(t_pipex *pipex, char *input_file, char *output_file)
{
	if (pipex->in_file == -1)
	{
		close(pipex->out_file);
		if (pipex->here_doc)
		{
			if (unlink(HERE_DOC_TMP_FILE) == -1)
			{
				print_perror(UNLINK_ERROR);
			}
			print_perror_exit(FILE_ERROR);
		}
		file_error_exit(input_file);
	}
	if (pipex->out_file == -1)
	{
		close(pipex->in_file);
		file_error_exit(output_file);
	}
}
