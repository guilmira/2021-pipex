/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:17:27 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/17 09:30:44 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int process_origin(int fd[2])
{
	int	ex_read;

	ex_read = fd[0];
	close(fd[1]);
	return (1);
}

int read_form_file(char *path)
{
	int fd;
	int gnl;
	char *line;
	

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (0);
	gnl = get_next_line(fd, &line);
	if (gnl < 1)
		return (0);
	return (1);
	
}

int process_son(int fd[2], char *path)
{
	int	ex_write;

	ex_write = fd[1];
	close(fd[0]);
	read_form_file(path);
	return (1);
}

int	parser(int argc, char *argv[])
{
	if (argc != 2)
		return (0);
	//check argv
	argv = (char **)argv;
	return (1);
}

void ft_shut(int i)
{
	exit(i);
}

int	main(int argc, char *argv[])
{
	int	fd[2];
	int	identifier;


	if (!parser(argc, argv))
		ft_shut(0);
	if (pipe(fd) == -1)
		ft_shut(0);
	identifier = fork();
	if (identifier > 0)
		process_origin(fd);
	else if (identifier == 0)
		process_son(fd, argv[1]);
	else
		exit(0);

	
	
	return (0);
}
