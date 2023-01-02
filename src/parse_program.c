/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:43:22 by cpalusze          #+#    #+#             */
/*   Updated: 2023/01/02 09:42:33 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*search_in_paths(char **paths, char *prog_name, int *error);
static char	**access_absolute_path(char **prog_with_args);
static void	alloc_error_exit(char **split);

// Search for program access, in PATH or absolute path
char	**parse_program(char *prog_name, t_pipex *pipex)
{
	char	**prog_args;
	char	*temp;
	int		alloc_error;

	alloc_error = 0;
	prog_args = ft_split(prog_name, ' ');
	if (prog_args == NULL)
		print_error_exit(ALLOC_ERROR);
	if (ft_strchr(prog_args[0], '/') != NULL)
		return (access_absolute_path(prog_args));
	temp = ft_strjoin("/", prog_args[0]);
	free(prog_args[0]);
	prog_args[0] = temp;
	if (prog_args[0] == NULL)
		alloc_error_exit(prog_args);
	prog_args[0] = search_in_paths(pipex->paths, prog_args[0], &alloc_error);
	if (alloc_error)
		alloc_error_exit(prog_args);
	return (prog_args);
}

// Search for PATH variable in environment
char	**get_paths(char **env)
{
	char	**paths;
	char	*path_env_var;
	int		i;

	i = 0;
	while (env[i])
	{
		path_env_var = ft_strnstr(env[i], PATH_PREFIX, ft_strlen(env[i]));
		if (path_env_var != NULL)
		{
			path_env_var += ft_strlen(PATH_PREFIX);
			break ;
		}
		i++;
	}
	if (i == 0)
		print_error_exit(PATH_ERROR);
	paths = ft_split(path_env_var, ':');
	return (paths);
}

static void	alloc_error_exit(char **split)
{
	free_split(split);
	print_error_exit(ALLOC_ERROR);
}

// Check for program access when the input is an absolute path
static char	**access_absolute_path(char **prog_with_args)
{
	if (access(prog_with_args[0], F_OK | X_OK) == 0)
		return (prog_with_args);
	print_perror_exit(prog_with_args[0]);
	free_split(prog_with_args);
	return (NULL);
}

// Check if we can find the program using env
// 		access: F_OK + X_OK => program exist and can be executed
static char	*search_in_paths(char **paths, char *prog_name, int *error)
{
	int		i;
	char	*prog_path;
	char	*join;

	i = -1;
	prog_path = NULL;
	while (paths[++i])
	{
		join = ft_strjoin(paths[i], prog_name);
		if (join == NULL)
		{
			*error = 1;
			break ;
		}
		if (access(join, F_OK | X_OK) == 0)
			prog_path = ft_strdup(join);
		free(join);
	}
	if (prog_path == NULL)
	{
		ft_printf_fd(STDERR_FILENO, "%s: ", prog_name + 1);
		ft_printf_fd(STDERR_FILENO, "command not found\n");
	}
	free(prog_name);
	return (prog_path);
}
