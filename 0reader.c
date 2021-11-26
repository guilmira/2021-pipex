/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0reader.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 14:35:55 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/26 15:42:23 by guilmira         ###   ########.fr       */
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

t_list *load_linked_list(char *argv[], char *envp[])
{
	int			i;
	char 		**folders;
	t_list		*lst;
	t_command	*command_struct;

	folders = get_env_path(envp);
	command_struct = ft_calloc(1, sizeof(t_command *));
	if (!command_struct) //check error
		return (NULL);
	int argc;
	argc = 2;
	i = -1;
	while (++i < argc)
	{
		command_struct->command = ft_split(argv[i + 2], ' ');
		command_struct->path = set_path(command_struct->command[0], folders);
		ft_lstadd_back(&lst, ft_lstnew(command_struct));
		if (!lst) //check error
			;
		
	}
	/* args->command1 = ft_split(argv[2], ' ');
	args->command2 = ft_split(argv[3], ' ');
	args->path1 = set_path(args->command1[0], folders);
	args->path2 = set_path(args->command2[0], folders); */

	ft_free_split(folders);
	return (lst);
}

/** PURPOSE : Load arguments into structure. */
t_arguments	*reader(char *argv[], char *envp[])
{
	
	t_arguments	*args;

	args = ft_calloc(1, sizeof(t_arguments));
	if (!args)
		ft_shut(MEM, 0);
	args->commands_lst = load_linked_list(argv, envp);
	/* if (!args->command1 || !args->command2 || \
	!args->path1 || !args->path2)
		ft_shut(ARG, 0); */
	args->file_input = argv[1];
	args->file_output = argv[4];
	return (args);
}