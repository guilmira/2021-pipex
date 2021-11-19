/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2son.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:47 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/19 12:03:55 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

# define FILE_NAME "outfile.txt"

static int read_form_file(char *path, char **line)
{
	int fd_file;
	int gnl;
	

	fd_file = open(path, O_RDONLY);
	if (fd_file < 0)
		ft_shut("Problem reading file\n", 1);
	gnl = get_next_line(fd_file, line);
	if (gnl < 0)
		ft_shut(GNL_ERROR, 1);
	return (1);
	
}

int process_son(int fd[2], char *path)
{
	int	ex_write;
	char *line;

	line = NULL;
	ex_write = fd[1];
	close(fd[0]);
	read_form_file(path, &line);
	//dup2(ex_write, STDOUT_FILENO);
	execlp("/bin/ls", "ls", "-l", NULL);
	write(ex_write, line, ft_strlen(line));
	exit(0);
}