/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpalusze <cpalusze@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 12:48:00 by cpalusze          #+#    #+#             */
/*   Updated: 2022/12/18 09:30:40 by cpalusze         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// Note: print on stderr ?
int	main(int argc, char **argv)
{
	int	file1;

	if (argc != 5)
		argument_error();
	file1 = open(argv[1], O_RDONLY);
	if (file1 == -1)
		file_error();
	// Get command 1

	// Exec command 1
}
