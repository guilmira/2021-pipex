/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4auxiliar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:04:00 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/27 12:30:32 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** PURPOSE : Free memory of program.
 * For the function to properly work, all pointers have been
 * initialized to NULL at the beginning of the program. */
void ft_clean(t_arguments *args)
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
