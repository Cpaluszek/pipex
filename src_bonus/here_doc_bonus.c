/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:00:03 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/02 10:17:16 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#define HERE_DOC_ARG "here_doc"
#define MIN_ARG_COUNT 5
#define HERE_DOC_START "heredoc> "
#define HERE_DOC_TMP_FILE ".heredoc.tmp"

int	count_args(char *arg, t_pipex *pipex)
{
	pipex->here_doc = (arg
			&& !ft_strncmp(HERE_DOC_ARG, arg, ft_strlen(HERE_DOC_ARG)));
	return (MIN_ARG_COUNT + pipex->here_doc);
}

// Note: what is unlink?
// Todo: check write error ?
void	here_doc(char *arg, t_pipex *pipex)
{
	int		file;
	char	*buffer;

	file = open(HERE_DOC_TMP_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file == -1)
		print_perror_exit(FILE_ERROR);
	while (1)
	{
		write(1, HERE_DOC_START, ft_strlen(HERE_DOC_START));
		buffer = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(arg, buffer, ft_strlen(arg) + 1))
			break ;
		write(file, buffer, ft_strlen(buffer));
		write(file, "\n", 1);
		free(buffer);
	}
	free(buffer);
	if (close(file) == -1)
		print_perror_exit(CLOSE_ERROR);
	pipex->in_file = open(HERE_DOC_TMP_FILE, O_RDONLY);
	if (pipex->in_file == -1)
	{
		unlink(HERE_DOC_TMP_FILE);
		print_perror_exit(FILE_ERROR);
	}
}
