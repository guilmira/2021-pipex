/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1parent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:44 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/22 15:56:23 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_to_file(int path, char *line)
{
	write(path, line, ft_strlen(line));
	write(path, "\n", 1);
	return (1);
}

int	parent_continues(void)
{
	/* int		fd_output;
	int		ex_read;
	char	*line;
	int		gnl; */

	/* usleep(1000);

	gnl = get_next_line(ex_read, &line);
	while (gnl)
	{
		write_to_file(fd_output, line);
		gnl = get_next_line(ex_read, &line);
	}
	if (gnl < 0)
		ft_shut(GNL_ERROR, 1);
	close(fd_output);
	close(ex_read); */
	return (1);
}

/** PURPOSE : Parent process function. */
int	process_origin(int fd[2], char *command2, char *path_out)
{
	int		identifier;
	int		ex_read;
	
	usleep(1000);
	ex_read = prepare_process(fd[0], fd[1]);
	identifier = fork();
	if (identifier == -1)
		ft_shut("Error at fork creation\n", 0);
	if (identifier == 0)
		second_son(ex_read, command2, path_out);
	else
		parent_continues();
	return (0);
}
