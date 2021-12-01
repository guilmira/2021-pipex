/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1parent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:44 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/01 10:28:47 by guilmira         ###   ########.fr       */
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
void	mid_process(t_arguments *args)
{
	int index;
	int status;
	int	identifier;

	usleep(1000);
	args->command_number++;
	index = args->command_number + 1; //seria el equivalente a fd[0];
	if (pipe(&args->fds[index]) == -1)
		ft_shut(MSG, 0);
	identifier = fork();
	if (identifier == 0)
	{
		close(args->fds[index]);
		mid_son(index, args);
	}
	else if (identifier > 0)
	{
		wait(&status);
		close(args->fds[index + 1]);
		return ;
	}
	else
		ft_shut("Error at fork creation\n", 0);

}
