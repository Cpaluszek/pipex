/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:47:45 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/03 14:16:05 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include "libft.h"

# define ARG_ERROR		"Invalid parameters:\n./pipex file1 cmd1 cmd2 file2\n"
# define ALLOC_ERROR	"Allocation error\n"
# define PATH_ERROR		"PATH not found\n"
# define FILE_ERROR		"File error"
# define FORK_ERROR		"Fork error"
# define DUP2_ERROR		"Error duplicating file descriptor"
# define CLOSE_ERROR	"Error closing file descriptor"
# define PIPE_ERROR		"Error creating pipe"
# define EXEC_ERROR		"Execution Error"
# define WRITE_ERROR	"Write Error"
# define CMD_NOT_FOUND	"command not found\n"

# define PATH_PREFIX		"PATH="
# define HERE_DOC_TMP_FILE	".heredoc.tmp"

typedef struct s_pipex
{
	char	**cmd_args;
	char	**env;
	char	**paths;
	int		*pipes;
	int		pipes_count;
	int		in_file;
	int		out_file;
	int		here_doc;
	int		cmd_count;
	int		child_id;
	pid_t	pid;
}	t_pipex;

/* Find Program	*/
char	**parse_program(char *prog_name, t_pipex *pipex);
char	**get_paths(char **env);

/*	Child	*/
void	child(t_pipex *pipex, char **argv);

/*	Errors	*/
void	print_error_exit(char *str);
void	print_perror_exit(char *str);
void	file_error_exit(char *str);

/*	Here_doc	*/
int		count_args(char *arg, t_pipex *pipex);
void	here_doc(char *arg, t_pipex *pipex);

/*	Files	*/
void	get_input_file(char **argv, t_pipex *pipex);
void	get_output_file(char *output_file, t_pipex *pipex);

/*	Utils	*/
void	parent_free(t_pipex *pipex);
void	close_pipes(t_pipex *pipex);
void	free_split(char **split);

#endif