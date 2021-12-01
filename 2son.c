/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2son.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:47 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/01 10:39:08 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	input_form_file(char *path)
{
	int	fd_file;

	fd_file = open(path, O_RDONLY);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_file, STDIN_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_file);
}

/** PURPOSE : Returns content of position 'n' of list.
 * Note: First element of the list is n = 0 */
void	*ft_lst_position(t_list *lst, int n)
{
	int	i;

	i = -1;
	if (!lst)
		return (NULL);
	while (++i < n)
	{
		if (!lst->next)
			return (NULL);
		else
			lst = lst->next;
	}
	return (lst->content);
}

void	first_son(t_arguments *args)
{
	int			fd_write;
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shut(LST, 0);
	fd_write = prepare_process(args->fds[0], args->fds[1]);
	if (args->flag_file)
		input_form_file(args->file_input);
	if (dup2(fd_write, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_write);
	if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shut(EXE_ERROR, 0);
}


static void	output_to_file(char *path)
{
	int	fd_file;

	fd_file = open(path, O_WRONLY | O_CREAT, FULL_PERMISSIONS);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_file, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_file);
}

/** PURPOSE : Last child process function. */
void	last_son(int index, t_arguments *args)
{	
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shut(LST, 0);	
	if (dup2(args->fds[index], STDIN_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(args->fds[index]);
	output_to_file(args->file_output);
	if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shut(EXE_ERROR, 0);
}

void	mid_son(int index, t_arguments *args)
{
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shut(LST, 0);
	if (dup2(args->fds[index - 2], STDIN_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(args->fds[index - 2]);
	if (dup2(args->fds[index + 1], STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(args->fds[index + 1]);
	if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shut(EXE_ERROR, 0);
}