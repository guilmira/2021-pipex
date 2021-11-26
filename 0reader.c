/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0reader.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:35:55 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/26 14:53:00 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char **get_full_path(char *envp[])
{
	int		i;
	
	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i], ':'));
	return (NULL);
}

static char	**add_slash_to_path(char **full_path)
{
	int i;
	char *added_slash;

	i = -1;
	while (full_path[++i])
	{
		added_slash = ft_strjoin(full_path[i], "/");
		if (!added_slash)
		{
			ft_free_split(full_path);
			return(NULL);
		}
		free(full_path[i]);
		full_path[i] = added_slash;
	}
	return(full_path);
}

static char **get_env_path(char *envp[])
{
	char	*new_string;
	char	**full_path;
	char	**corrected_path;

	full_path = get_full_path(envp);
	if (!full_path)
		return (NULL);
	new_string = ft_strdup(ft_strchr(full_path[0], '/'));
	if (!new_string)
	{
		ft_free_split(full_path);
		return (NULL);
	}
	free(full_path[0]);
	full_path[0] = new_string;
	corrected_path = add_slash_to_path(full_path);
	if (!corrected_path)
		return (NULL);
	return (corrected_path);
}

/** PURPOSE : Load arguments into structure. */
void	reader(char *argv[], t_command *args, char *envp[])
{
	char **folders;
	int i;
	i = -1;
	folders = get_env_path(envp);
	args->command1 = ft_split(argv[2], ' ');
	args->command2 = ft_split(argv[3], ' ');
	args->path1 = set_path(args->command1[0], folders);
	args->path2 = set_path(args->command2[0], folders);
	ft_free_split(folders);
	if (!args->command1 || !args->command2 || \
	!args->path1 || !args->path2)
		ft_shut(ARG, 0);
	args->file_input = argv[1];
	args->file_output = argv[4];
}