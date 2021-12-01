/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4auxiliar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:04:00 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/01 13:13:04 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** PURPOSE : Free memory of program.
 * For the function to properly work, all pointers have been
 * initialized to NULL at the beginning of the program. */
void	ft_clean(t_arguments *args)
{
	if (args)
	{
		if (args)
		{
			//ft_free_split(args->command1);
			//ft_free_split(args->command2);
			//free(args->path1);
			//free(args->path2);
		}
		free(args);
	}
}

/** PURPOSE : Output error with given value 1, close the program.
 * If exit signal is 0, it will prevent the appeareance of message:
 * "make: *** [exe] Error 1" */
void	ft_shut(char *str, int i)
{
	write(1, str, ft_strlen(str));
	exit(i);
}

/** PURPOSE : Does the path of the command exist? Returns bool. */
int	file_exists(char *str)
{
	int	fp;

	fp = open(str, O_RDONLY);
	if (fp == -1)
		return (0);
	close(fp);
	return (1);
}

/** PURPOSE : Build an int array with every file descriptor of pipes. */
int	*arg_descriptors(t_arguments *args)
{
	int	*ptr;
	int	number_of_fds;

	number_of_fds = (args->total_commands - 1) * 2;
	ptr = ft_calloc(number_of_fds, sizeof(int));
	if (!ptr)
		ft_shut(MEM, 0);
	return (ptr);
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
