/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2son.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:47 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/24 12:56:51 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	input_form_file(char *path)
{
	int	fd_file;

	fd_file = open(path, O_RDONLY);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_file, STDIN_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_file);
	return (1);
}

/** PURPOSE : Child process function. */
void	process_son(int fd[2], char *path_file, char **command1, char *path_command)
{
	int		ex_write;

	ex_write = prepare_process(fd[0], fd[1]);
	input_form_file(path_file);
	if (dup2(ex_write, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(ex_write);
	if (execve(path_command, command1, NULL) == -1)
		ft_shut("Error with execve\n", 0);
}

/** PURPOSE : Second child process function. */
void	second_son(int ex_read, char **command2, char *path_command, char *path_file)
{
	int		fd_output;

	if (dup2(ex_read, STDIN_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(ex_read);
	fd_output = open(path_file, O_WRONLY | O_CREAT, FULL_PERMISSIONS);
	if (fd_output < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_output, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	if (execve(path_command, command2, NULL) == -1)
		ft_shut("Error with execve at wc\n", 0);
		//habria que cerrar el fd_output y para ello ahcer el open fueera
}