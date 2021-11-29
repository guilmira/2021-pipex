/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1parent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:44 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/29 12:28:49 by guilmira         ###   ########.fr       */
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

static void	process_end(t_arguments *args)
{
	//close_fd();
	clean_memory(args);
	//printf("%s\n", args->path1);
}

/** PURPOSE : Parent process function. */
int	parent_continues(int fd[2], t_arguments *args)
{
	int		identifier;
	int status;
	usleep(1000);
	close(fd[1]);
	
	args->command_number++;
	
	identifier = fork();
	if (identifier == 0)
		last_son(fd, args);
	else if (identifier > 0)
	{
		wait(&status);
		process_end(args);
	}
	else
		ft_shut("Error at fork creation\n", 0);
	return (0);
}

/** PURPOSE : Mid process continue function. */
int	mid_process(int fd[2], t_arguments *args)
{
	int		identifier;
	int		fd_mid[2];
	int status;

	usleep(1000);
	close(fd[1]);
	if (pipe(fd_mid) == -1)
		ft_shut(MSG, 0);
	args->command_number++;
	identifier = fork();
	if (identifier == 0)
	{
		close(fd_mid[0]);
		mid_son(fd[0], fd_mid[1], args);
	}
	else if (identifier > 0)
	{
		wait(&status);
		close(fd_mid[1]);
		return (0);
	}
	else
		ft_shut("Error at fork creation\n", 0);
	return (0);
}
