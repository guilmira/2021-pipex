/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:17:27 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/23 13:42:55 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** EXECUTION : /pipex file1 command1 command2 file2
 * The program will mimic the behaviour of '|' in shell.
 * 1. Parser arguments.
 * 2. Execute pipe and fork main process.
 * 3. Child process will 
 * 4. Parent process will read command and write it to file. */
int	main(int argc, char *argv[])
{
	int	fd[2];
	int	identifier;
	//int status;

	if (!parser(argc, argv))
		ft_shut(ARG, 0);
	if (pipe(fd) == -1)
		ft_shut(MSG, 0);
	identifier = fork();
	if (identifier == 0)
		process_son(fd, argv[1]);
	else if (identifier > 0)
		process_origin(fd, argv[3], argv[4]);
	else
		ft_shut("Error at fork creation\n", 0);
	exit(0);
	return (0);
}

//close ld file descrptors after using dup2
