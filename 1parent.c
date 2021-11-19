/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1parent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:44 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/19 12:48:55 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


int write_to_file(int path, char *line)
{
	
	write(path, line, ft_strlen(line));
	write(path, "\n", 1);
	return (1);
}

int process_origin(int fd[2], char *path)
{
	int	ex_read;
	char *line;
	int gnl;
	int fd_output;

	ex_read = prepare_process(fd[0], fd[1]);
	fd_output = open(path, O_CREAT, O_WRONLY, O_APPEND);
	if (fd_output < 0)
		ft_shut("failure at file\n", 1);
	gnl = get_next_line(ex_read, &line);
	while (gnl)
	{
	
		write_to_file(fd_output, line);
		gnl = get_next_line(ex_read, &line);
	}
	if (gnl < 0)
			ft_shut(GNL_ERROR, 1);
	close(fd_output);
	close(ex_read);
	return (1);
}