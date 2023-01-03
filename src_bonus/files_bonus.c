/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:56:27 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/03 14:17:55 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>

// Note: what is unlink?
// Open input file, or manage here_doc
void	get_input_file(char **argv, t_pipex *pipex)
{
	if (pipex->here_doc)
	{
		here_doc(argv[2], pipex);
		pipex->in_file = open(HERE_DOC_TMP_FILE, O_RDONLY);
		if (pipex->in_file == -1)
		{
			unlink(HERE_DOC_TMP_FILE);
			print_perror_exit(FILE_ERROR);
		}
	}
	else
	{
		pipex->in_file = open(argv[1], O_RDONLY);
		if (pipex->in_file == -1)
			file_error_exit(argv[1]);
	}
}

// Open or create the output file with truncation
// If 1st param is here_doc append to the output file instead of truncate
void	get_output_file(char *output_file, t_pipex *pipex)
{
	if (pipex->here_doc)
		pipex->out_file = open(output_file, O_CREAT | O_APPEND | O_RDWR, 0644);
	else
		pipex->out_file = open(output_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pipex->out_file == -1)
		print_perror_exit(FILE_ERROR);
}
