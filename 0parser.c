/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0parser.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:03:27 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/29 11:21:38 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** PURPOSE : Check argument counter.
 * This parser does not check the values themselves off argv. */
int	parser(int argc, char *argv[])
{
	if (argc < ARGUMENTS)
		return (0);
	argv = (char **)argv;
	return (1);
}

/** PURPOSE : Close fork file pointer replica not to be used. */
int	prepare_process(int fd_to_close, int fd_to_prepare)
{
	close(fd_to_close);
	return (fd_to_prepare);
}



/** PURPOSE : Checks whether command exists and if it does,
 * returns full path to it. */
char	*set_path(char *command, char **folders)
{
	int	i;
	char *command_path;

	i = -1;
	while (folders[++i])
	{
		command_path = ft_strjoin(folders[i], command);
		if (file_exists(command_path))
			return(command_path);
		free(command_path);
	}
	return (NULL);
}