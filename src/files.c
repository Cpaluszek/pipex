/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/03 13:16:19 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/03 16:27:41 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "pipex.h"

// Open input file, create or open with truncation the output file
void	open_files(t_pipex *pipex, char *input, char *output)
{
	pipex->in_file = open(input, O_RDONLY);
	if (pipex->in_file == -1)
		file_error_exit(input);
	pipex->out_file = open(output, O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (pipex->out_file == -1)
		print_perror_exit(FILE_ERROR);
}
