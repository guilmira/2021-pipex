/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2son.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:47 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/22 16:21:02 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	read_form_file(char *path, char **line)
{
	int	fd_file;
	int	gnl;

	fd_file = open(path, O_RDONLY);
	if (fd_file < 0)
		ft_shut("Problem reading file\n", 1);
	gnl = get_next_line(fd_file, line);
	if (gnl < 0)
		ft_shut(GNL_ERROR, 1);
	close(fd_file);
	return (1);
}

/** PURPOSE : Child process function. */
int	process_son(int fd[2], char *path)
{
	int		ex_write;
	char	*line;
	char	**table;
	char	*command_path;

	line = NULL;
	ex_write = prepare_process(fd[1], fd[0]);
	read_form_file(path, &line);
	table = ft_split(line, ' ');
	command_path = ft_strjoin(PATH_BIN, table[0]);
	if (dup2(ex_write, STDOUT_FILENO) == -1)
		ft_shut("Error with dup2\n", 0);
	if (execve(command_path, table, NULL) == -1)
		ft_shut("Error with execve\n", 0);
	//close(ex_write); esto ya no se eecuta, y se cierra en padre
	exit(0); //tampoco se ejecuta
}

/** PURPOSE : Second child process function. */
int	second_son(int ex_read, char *command2, char *path_out)
{
	char	*line;
	char	*command_path;
	char	**table;
	int		fd_output;

	line = NULL;
	table = ft_split(command2, ' ');
	command_path = ft_strjoin(PATH_USR, table[0]);
	if (dup2(ex_read, STDIN_FILENO) == -1)
		ft_shut("Error with dup2\n", 0);
	close(ex_read);
	fd_output = open(path_out, O_WRONLY | O_CREAT, FULL_PERMISSIONS);
	if (fd_output < 0)
		ft_shut("Failure at opening file\n", 1);
	if (dup2(fd_output, STDOUT_FILENO) == -1)
		ft_shut("Error with dup2\n", 0);
	if (execve(command_path, table, NULL) == -1)
		ft_shut("Error with execve at wc\n", 0);
		//habria que cerrar el fd_output y para ello ahcer el open fueera
	return(0);
}