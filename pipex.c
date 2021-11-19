/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:17:27 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/19 12:04:28 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[])
{
	int	fd[2];
	int	identifier;
	//int status;

	if (!parser(argc, argv))
		ft_shut(ARG, 0);
	if (pipe(fd) == -1)
		ft_shut(MSG, 0);
	identifier = fork();
	if (identifier > 0)
		process_origin(fd);
	else if (identifier == 0)
		process_son(fd, argv[1]);
	else
		exit(0);
	return (0);
}

/* #include <unistd.h>
int main(void)
{
	//ejecutar comandos
	execlp("/bin/ls", "ls", "-l", NULL);
	return (0);
} */