/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:47:45 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/05 15:23:26 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft.h"
# include <unistd.h>

# define ARG_ERROR		"Invalid parameters:\n./pipex file1 cmd1 cmd2 file2\n"
# define ALLOC_ERROR	"Allocation error\n"
# define PATH_ERROR		"PATH not found\n"
# define FILE_ERROR		"File error"
# define FORK_ERROR		"Fork error"
# define DUP2_ERROR		"Error duplicating file descriptor"
# define CLOSE_ERROR	"Error closing file descriptor"
# define PIPE_ERROR		"Error creating pipe"
# define EXEC_ERROR		"Execution Error"
# define CMD_NOT_FOUND	"command not found\n"

# define PATH_PREFIX	"PATH="

typedef struct s_pipex
{
	char	**first_cmd;
	char	**second_cmd;
	char	**env;
	char	**paths;
	int		pipe[2];
	int		in_file;
	int		out_file;
	pid_t	pid1;
	pid_t	pid2;
}	t_pipex;

/* Find Program	*/
char	**parse_program(char *prog_name, t_pipex *pipex);
char	**get_paths(char **env, char *first_cmd, char *second_cmd);

/*	Exec	*/
void	execute_first_program(t_pipex *pipex, char *input);
void	execute_second_program(t_pipex *pipex, char *output);

/*	Errors	*/
void	print_error_exit(char *str);
void	print_perror_exit(char *str);
void	file_error_exit(char *str);

/*	Files	*/
void	open_files(t_pipex *pipex, char *input, char *output);

/*	Utils	*/
void	parent_free(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	free_split(char **split);

#endif