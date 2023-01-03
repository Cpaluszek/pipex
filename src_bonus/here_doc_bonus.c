/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:00:03 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/03 14:17:57 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#define HERE_DOC_ARG "here_doc"
#define MIN_ARG_COUNT 5
#define HERE_DOC_START "heredoc> "

// Count arguments and check for here_doc parameter
int	count_args(char *arg, t_pipex *pipex)
{
	pipex->here_doc = (arg
			&& !ft_strncmp(HERE_DOC_ARG, arg, ft_strlen(HERE_DOC_ARG)));
	return (MIN_ARG_COUNT + pipex->here_doc);
}

// Read input from STDIN and write to temporary here_doc file
void	here_doc(char *arg, t_pipex *pipex)
{
	int		file;
	char	*buffer;

	file = open(HERE_DOC_TMP_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file == -1)
		print_perror_exit(FILE_ERROR);
	while (1)
	{
		buffer = get_next_line(STDIN_FILENO);
		if (!ft_strncmp(arg, buffer, ft_strlen(arg)))
			break ;
		if (write(file, buffer, ft_strlen(buffer)) == -1)
		{
			free(buffer);
			print_perror_exit(WRITE_ERROR);
		}
		free(buffer);
	}
	free(buffer);
	if (close(file) == -1)
		print_perror_exit(CLOSE_ERROR);
	pipex->in_file = open(HERE_DOC_TMP_FILE, O_RDONLY);
}
