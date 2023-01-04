/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 09:56:27 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/04 12:59:48 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>

// Open input file, or manage here_doc
// Open or create the output file with truncation
// If 1st param is here_doc append to the output file instead of truncate
void	get_files(char **argv, char *output_file, t_pipex *pipex)
{
	if (pipex->here_doc)
	{
		here_doc(argv[2]);
		pipex->in_file = open(HERE_DOC_TMP_FILE, O_RDONLY);
		pipex->out_file = open(output_file,
				O_CREAT | O_APPEND | O_WRONLY, 0644);
	}
	else
	{
		pipex->in_file = open(argv[1], O_RDONLY);
		pipex->out_file = open(output_file, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	}
}
