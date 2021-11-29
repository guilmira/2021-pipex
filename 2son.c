/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2son.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:47 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/29 12:40:43 by guilmira         ###   ########.fr       */
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

void	first_son(int fd[2], t_arguments *args)
{
	int			ex_write;
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shut(LST, 0);
	ex_write = prepare_process(fd[0], fd[1]);
	if (args->flag_file)
		input_form_file(args->file_input);
	if (dup2(ex_write, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(ex_write);
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
void	last_son(int fd_read, t_arguments *args)
{	
	int			ex_read;
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shut(LST, 0);
	ex_read = fd_read;
	if (dup2(ex_read, STDIN_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(ex_read);
	output_to_file(args->file_output);
	if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shut(EXE_ERROR, 0);
}

void	mid_son(int fd_previous_read, int fd_next_write, t_arguments *args)
{
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, args->command_number);
	if (!command_struct)
		ft_shut(LST, 0);
	if (dup2(fd_previous_read, STDIN_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_previous_read);
	if (dup2(fd_next_write, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_next_write);
	if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shut(EXE_ERROR, 0);
}