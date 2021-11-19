/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2son.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:47 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/19 12:40:22 by guilmira         ###   ########.fr       */
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
	close(fd_file);
	return (1);
	
}

int process_son(int fd[2], char *path)
{
	int	ex_write;
	char *line;
	char **table;
	char *command_path;

	line = NULL;
	ex_write = prepare_process(fd[1], fd[0]);
	read_form_file(path, &line);
	table = ft_split(line, ' ');
	command_path = ft_strjoin(PATH_BIN, table[0]);
	dup2(ex_write, STDOUT_FILENO);
	execlp(command_path, table[0], table[1], NULL);
	//close(ex_write);
	exit(0);
}