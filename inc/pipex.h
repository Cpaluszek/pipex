/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:47:45 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/18 13:15:45 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# include "libft.h"

// Todo: look for static functions

/* Find Program	*/
char	**parse_program(char *prog_name, char **env);

/*	Errors	*/
void	argument_error(void);
void	file_error(void);
void	program_error(void);
void	allocation_error(void);

/*	Utils	*/
void	free_split(char **split);

#endif