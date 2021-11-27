/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:17:27 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/27 11:06:36 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


/** PURPOSE : shutdown program freeing heap allocated memory.
 * 1. Clean memory for argument.
 * 3. Print error message. */
//void	ft_shutdown(t_time *arg)


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
	t_arguments	*args;
	//int status;
	t_command *ptr;
	ptr = args->commands_lst->content;
	
	args = NULL;
	if (!parser(argc, argv))
		ft_shut(ARG, 0);
	args = arg_reader(argv, envp);
	if (pipe(fd) == -1)
		ft_shut(MSG, 0);
	identifier = fork();
	if (identifier == 0)
		process_son(fd, args->file_input, \
		ptr->command, ptr->path);
	else if (identifier > 0)
		process_origin(fd, args);
	else
		ft_shut("Error at fork creation\n", 0);
	//wait()
	ft_clean(args);
	exit(0);
}

//close ld file descrptors after using dup2
