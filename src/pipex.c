/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/18 10:21:02 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*find_program(char *prog_name, char **env);
char	**get_paths(char **env);

int	main(int argc, char **argv, char **env)
{
	int		file1;
	// int		exec_ret;
	char	*prog_path;

	if (argc != 5)
		argument_error();
	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
		file_error();

	prog_path = find_program(argv[2], env);
	// exec_ret = execve(argv[2], argv + 2, env);
	// if (exec_ret == -1)
	// 	program_error();
}

// Note: check env for null ?
// Todo: check if prog_name contains a /
char	*find_program(char *prog_name, char **env)
{
	int		i;
	char	**paths;
	char	*join;

	i = 0;
	paths = get_paths(env);
	if (paths == NULL)
		allocation_error();
	// Todo: free join
	if (ft_strchr(prog_name, '/') == NULL)
	{
		prog_name = ft_strjoin("/", prog_name);
		if (prog_name == NULL)
			allocation_error();
	}
	while (paths[i])
	{
		// Check if we can access file
		join = ft_strjoin(paths[i], prog_name);
		printf("Searching for: %s\n", join);
		if (access(join, F_OK | X_OK) == 0)
			printf("We found: %s\n", join);
		free(paths[i]);
		free(join);
		i++;
	}
	free(paths);
	return (paths[0]);
}

char	**get_paths(char **env)
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