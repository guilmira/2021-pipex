/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1parent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:44 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/26 15:15:36 by guilmira         ###   ########.fr       */
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
		if (args->command1)
		{
			free(args->command1);
			free(args->command2);
			free(args->path1);
			free(args->path2);
			/* free(args->file_input);
			free(args->file_output); */
		}
	}
}

void	parent_continues(t_arguments *args)
{
	//close_fd();
	clean_memory(args);
	//printf("%s\n", args->path1);
}

/** PURPOSE : Parent process function. */
int	process_origin(int fd[2], t_arguments *args)
{
	int		identifier;
	int		ex_read;
	
	usleep(1000);
	ex_read = prepare_process(fd[1], fd[0]);
	identifier = fork();
	if (identifier == 0)
		second_son(ex_read, args->command2,\
		args->path2, args->file_output);
	else if (identifier > 0)
		parent_continues(args);
	else
		ft_shut("Error at fork creation\n", 0);
	return (0);
}
