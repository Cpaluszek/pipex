/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/18 10:43:22 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/18 15:15:58 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**get_paths(char **env);
static char	*search_in_paths(char **paths, char *prog_name);

// Todo: find a better file name

// Note: check env for null ?
// Note: join in temp to free previous?
char	**parse_program(char *prog_name, char **env)
{
	char	**paths;
	char	**prog_with_args;

	paths = get_paths(env);
	if (paths == NULL)
		allocation_error();
	prog_with_args = ft_split(prog_name, ' ');
	if (prog_with_args == NULL)
	{
		free_split(paths);
		allocation_error();
	}
	if (ft_strchr(prog_with_args[0], '/') == NULL)
	{
		prog_with_args[0] = ft_strjoin("/", prog_with_args[0]);
		if (prog_with_args[0] == NULL)
		{
			free_split(paths);
			free_split(prog_with_args);
			allocation_error();
		}
	}
	prog_with_args[0] = search_in_paths(paths, prog_with_args[0]);
	return (prog_with_args);
}

// Check if we can find the program using env
// 		access: F_OK + X_OK => program exist and can be executed
// Note: is malloc protection on join needed?
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
		path_env_var = ft_strnstr(env[i], "PATH=", ft_strlen(env[i]));
		if (path_env_var != NULL)
			break ;
		i++;
	}
	paths = ft_split(path_env_var, ':');
	return (paths);
}
