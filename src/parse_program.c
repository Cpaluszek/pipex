/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:43:22 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/19 13:10:35 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_paths(char **env);
static char	*search_in_paths(char **paths, char *prog_name);
static char	**access_absolute_path(char **prog_with_args);
static void	alloc_error(char **split);

char	**parse_program(char *prog_name, char **env)
{
	char	**paths;
	char	**prog_with_args;
	char	*temp;

	prog_with_args = ft_split(prog_name, ' ');
	if (prog_with_args == NULL)
		print_error_exit(ALLOC_ERROR);
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
	print_error_exit(ALLOC_ERROR);
}

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
		print_error_exit(PATH_ERROR);
	paths = ft_split(path_env_var, ':');
	return (paths);
}
