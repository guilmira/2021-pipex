/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2son.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:47 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/27 13:05:11 by guilmira         ###   ########.fr       */
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

void	first_son(int fd[2], t_arguments *args, int command_number)
{
	int			ex_write;
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, command_number);
	if (!command_struct)
		ft_shut(LST, 0);
	ex_write = prepare_process(fd[0], fd[1]);
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

	printf("%s\n", path);
	fd_file = open(path, O_WRONLY | O_CREAT, FULL_PERMISSIONS);
	if (fd_file < 0)
		ft_shut(FILE_ERROR, 1);
	if (dup2(fd_file, STDOUT_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(fd_file);
}

/** PURPOSE : Last child process function. */
void	last_son(int fd[2], t_arguments *args, int command_number)
{	
	int			ex_read;
	t_command	*command_struct;

	command_struct = NULL;
	command_struct = ft_lst_position(args->commands_lst, command_number);
	if (!command_struct)
		ft_shut(LST, 0);
	ex_read = fd[0];
	if (dup2(ex_read, STDIN_FILENO) == -1)
		ft_shut(DUP_ERROR, 0);
	close(ex_read);
	output_to_file(args->file_output);
	if (execve(command_struct->path, command_struct->command, NULL) == -1)
		ft_shut(EXE_ERROR, 0);
}