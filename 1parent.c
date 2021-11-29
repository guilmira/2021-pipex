/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1parent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:44 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/29 12:39:06 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_to_file(int path, char *line)
{
	write(path, line, ft_strlen(line));
	write(path, "\n", 1);
	return (1);
}

void	clean_memory(t_arguments *args)
{
	if (args)
	{
		if (args)
		{
			;
			/* free(args->command1);
			free(args->command2);
			free(args->path1);
			free(args->path2); */
			/* free(args->file_input);
			free(args->file_output); */
		}
	}
}



/** PURPOSE : Mid process continue function. */
int	mid_process(int fd_read, t_arguments *args)
{
	int		identifier;
	int		fd_mid[2];
	int status;

	usleep(1000);
	
	if (pipe(fd_mid) == -1)
		ft_shut(MSG, 0);
	args->command_number++;
	identifier = fork();
	if (identifier == 0)
	{
		close(fd_mid[0]);
		mid_son(fd_read, fd_mid[1], args);
	}
	else if (identifier > 0)
	{
		wait(&status);
		close(fd_mid[1]);
		return (fd_mid[0]);
	}
	else
		ft_shut("Error at fork creation\n", 0);
	return (0);
}
