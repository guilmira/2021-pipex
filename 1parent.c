/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1parent.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:44 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/19 11:04:29 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int process_origin(int fd[2])
{
	int	ex_read;
	char *line;
	int gnl;

	ex_read = fd[0];
	close(fd[1]);
	gnl = get_next_line(ex_read, &line);
	if (gnl < 0)
		ft_shut(GNL_ERROR, 1);
	printf("%s\n", line);
	return (1);
}