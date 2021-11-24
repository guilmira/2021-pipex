/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:17:27 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/24 13:05:45 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"



int	reader(char *argv[], t_command *command_list)
{
	command_list->command1 = ft_split(argv[2], ' ');
	command_list->command2 = ft_split(argv[3], ' ');
	command_list->path1 = ft_strjoin(PATH_BIN, command_list->command1[0]);
	command_list->path2 = ft_strjoin(PATH_USR, command_list->command2[0]);
	if (!command_list->command1 || !command_list->command2 || \
	!command_list->path1 || !command_list->path2)
		ft_shut(ARG, 0);
	command_list->file_input = argv[1];
	command_list->file_output = argv[4];
	return (0);
}

/** EXECUTION : /pipex file1 command1 command2 file2
 * The program will mimic the behaviour of '|' in shell.
 * 1. Parser arguments.
 * 2. Execute pipe and fork main process.
 * 3. Child process will 
 * 4. Parent process will read command and write it to file. */
int	main(int argc, char *argv[], char *envp[])
{
	int			fd[2];
	int			identifier;
	t_command	*command_list;
	//int status;

	int i = -1;
	while (envp[++i])
		i++;
	
	command_list = ft_calloc(1, sizeof(t_command));
	if (!command_list)
		ft_shut(MEM, 0);
	if (!parser(argc, argv))
		ft_shut(ARG, 0);
	
	reader(argv, command_list);
	if (pipe(fd) == -1)
		ft_shut(MSG, 0);
	identifier = fork();
	if (identifier == 0)
		process_son(fd, command_list->file_input,\
		command_list->command1, command_list->path1);
	else if (identifier > 0)
		process_origin(fd, command_list);
	else
		ft_shut("Error at fork creation\n", 0);
	//wait()
	exit(0);
}

//close ld file descrptors after using dup2
