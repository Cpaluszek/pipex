/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:43:22 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 12:01:55 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_paths(char **env);
static char	*search_in_paths(char **paths, char *prog_name);
static char	**access_absolute_path(char **prog_with_args);
static void	alloc_error(char **split);

// Todo: find a better file name
// Note: custom print function for access error?
char	**parse_program(char *prog_name, char **env)
{
	char	**paths;
	char	**prog_with_args;
	char	*temp;

	prog_with_args = ft_split(prog_name, ' ');
	if (prog_with_args == NULL)
		print_error_exit(ALLOC_ERROR, 4);
	if (ft_strchr(prog_with_args[0], '/') != NULL)
		return (access_absolute_path(prog_with_args));
	temp = ft_strjoin("/", prog_with_args[0]);
	free(prog_with_args[0]);
	prog_with_args[0] = temp;
	if (prog_with_args[0] == NULL)
		alloc_error(prog_with_args);
	paths = get_paths(env);
	if (paths == NULL)
		alloc_error(prog_with_args);
	prog_with_args[0] = search_in_paths(paths, prog_with_args[0]);
	return (prog_with_args);
}

static void	alloc_error(char **split)
{
	free_split(split);
	print_error_exit(ALLOC_ERROR, 4);
}

static char	**access_absolute_path(char **prog_with_args)
{
	if (access(prog_with_args[0], F_OK | X_OK) == 0)
		return (prog_with_args);
	ft_printf_fd(STDERR_FILENO, prog_with_args[0]);
	print_error_exit(": Can't be accessed\n", 6);
	free_split(prog_with_args);
	return (NULL);
}

// Check if we can find the program using env
// 		access: F_OK + X_OK => program exist and can be executed
// Note: is malloc protection on join needed? or dup?
static char	*search_in_paths(char **paths, char *prog_name)
{
	int		i;
	char	*prog_path;
	char	*join;

	i = 0;
	while (paths[i])
	{
		join = ft_strjoin(paths[i], prog_name);
		if (access(join, F_OK | X_OK) == 0)
			prog_path = ft_strdup(join);
		free(join);
		i++;
	}
	free_split(paths);
	free(prog_name);
	return (prog_path);
}

// Todo: rename env error?
static char	**get_paths(char **env)
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
		print_error_exit(ENV_ERROR, 5);
	paths = ft_split(path_env_var, ':');
	return (paths);
}
