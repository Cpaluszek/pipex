/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:47:45 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 13:10:13 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# include "libft.h"

// Todo: look for static functions
// Todo: header file for errors?
// Todo: define errors codes
# define ARG_ERROR		"Invalid parameters:\n./pipex file1 cmd1 cmd2 file2\n"
# define ALLOC_ERROR	"Allocation error\n"
# define PATH_ERROR		"PATH not found\n"
# define FILE_ERROR		"File error"
# define FORK_ERROR		"Fork error"
# define DUP2_ERROR		"Error duplicating file descriptor"
# define CLOSE_ERROR	"Error closing file descriptor"
# define EXEC_ERROR		"Error executing program"

# define PATH_PREFIX	"PATH="

/* Find Program	*/
char	**parse_program(char *prog_name, char **env);

/*	Exec	*/
void	execute_program(int input_fd, char **prog_with_args, char **env);

/*	Errors	*/
void	print_error_exit(char *str);
void	print_perror_exit(char *str);

/*	Utils	*/
void	free_split(char **split);
char	*join_and_free(char *s1, char *s2);

#endif