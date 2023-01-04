/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:00:03 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/04 13:20:29 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <fcntl.h>
#define HERE_DOC_ARG "here_doc"
#define MIN_ARG_COUNT 5
#define HERE_DOC_SYM "heredoc> "

static void	manage_here_doc_input(char *arg, int file);

// Count arguments and check for here_doc parameter
int	count_args(char *arg, t_pipex *pipex)
{
	pipex->here_doc = (arg
			&& !ft_strncmp(HERE_DOC_ARG, arg, ft_strlen(HERE_DOC_ARG)));
	return (MIN_ARG_COUNT + pipex->here_doc);
}

// Read input from STDIN and write to temporary here_doc file
void	here_doc(char *arg)
{
	int		file;
	char	*delimiter;

	file = open(HERE_DOC_TMP_FILE, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (file == -1)
		print_perror_exit(FILE_ERROR);
	delimiter = ft_strjoin(arg, "\n");
	if (delimiter == NULL)
		print_error_exit(ALLOC_ERROR);
	manage_here_doc_input(delimiter, file);
	free(delimiter);
	if (close(file) == -1)
		print_perror_exit(CLOSE_ERROR);
}

static void	manage_here_doc_input(char *delimiter, int file)
{
	char	*buffer;

	while (1)
	{
		if (write(STDOUT_FILENO, HERE_DOC_SYM, ft_strlen(HERE_DOC_SYM)) == -1)
		{
			free(delimiter);
			if (close(file) == -1)
				print_perror(CLOSE_ERROR);
			print_perror_exit(WRITE_ERROR);
		}
		buffer = get_next_line(STDIN_FILENO);
		if (ft_strnstr(buffer, delimiter, ft_strlen(buffer)) == buffer)
			break ;
		if (write(file, buffer, ft_strlen(buffer)) == -1)
		{
			free(buffer);
			free(delimiter);
			if (close(file) == -1)
				print_perror(CLOSE_ERROR);
			print_perror_exit(WRITE_ERROR);
		}
		free(buffer);
	}
	free(buffer);
}
