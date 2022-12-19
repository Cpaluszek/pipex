/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:47:45 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 10:40:40 by cpalusze         ###   ########.fr       */
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
# define ARG_ERROR		"Invalid parameters:\n./pipex file1 cmd1 cmd2 file2\n"
# define ALLOC_ERROR	"Allocation error\n"
# define ENV_ERROR		"Environment error\n"
# define FILE_ERROR		"File error"

# define PATH_PREFIX	"PATH="

/* Find Program	*/
char	**parse_program(char *prog_name, char **env);

/*	Exec	*/
void	execute_program(int input_fd, char **prog_with_args, char **env);

/*	Errors	*/
void	print_error_exit(char *str, int err_code);
void	print_sys_error_exit(char *str, int err_code);

/*	Utils	*/
void	free_split(char **split);
char	*join_and_free(char *s1, char *s2);

#endif