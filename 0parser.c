/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:27 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/19 12:35:33 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	parser(int argc, char *argv[])
{
	if (argc != ARGUMENTS)
		return (0);
	//check argv
	argv = (char **)argv;
	return (1);
}

int	prepare_process(int fd_to_prepare, int fd_to_close)
{
	close(fd_to_close);
	return (fd_to_prepare);
}