/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1parent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:44 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/24 13:06:21 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	write_to_file(int path, char *line)
{
	write(path, line, ft_strlen(line));
	write(path, "\n", 1);
	return (1);
}

void	clean_memory(t_command *command_list)
{
	if (command_list)
	{
		if (command_list->command1)
		{
			free(command_list->command1);
			free(command_list->command2);
			free(command_list->path1);
			free(command_list->path2);
			/* free(command_list->file_input);
			free(command_list->file_output); */
		}
	}
}

void	parent_continues(t_command *command_list)
{
	//close_fd();
	clean_memory(command_list);
	//printf("%s\n", command_list->path1);
}

/** PURPOSE : Parent process function. */
int	process_origin(int fd[2], t_command *command_list)
{
	int		identifier;
	int		ex_read;
	
	usleep(1000);
	ex_read = prepare_process(fd[1], fd[0]);
	identifier = fork();
	if (identifier == 0)
		second_son(ex_read, command_list->command2,\
		command_list->path2, command_list->file_output);
	else if (identifier > 0)
		parent_continues(command_list);
	else
		ft_shut("Error at fork creation\n", 0);
	return (0);
}
