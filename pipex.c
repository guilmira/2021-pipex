/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:17:27 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/01 09:06:13 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


/** PURPOSE : shutdown program freeing heap allocated memory.
 * 1. Clean memory for argument.
 * 3. Print error message. */
//void	ft_shutdown(t_time *arg)

/* static void	process_end(t_arguments *args)
{
	//close_fd();
	;
	//clean_memory(args);
	//printf("%s\n", args->path1);
} */

/** PURPOSE : Parent process function. */
static int	parent_continues(int fd_read, t_arguments *args)
{
	int	identifier;
	int	status;

	usleep(1000);
	args->command_number++;
	identifier = fork();
	if (identifier == 0)
		last_son(fd_read, args);
	else if (identifier > 0)
	{
		wait(&status);
		//process_end(args);
	}
	else
		ft_shut("Error at fork creation\n", 0);
	return (0);
}

int	*arg_descriptors(t_arguments *args)
{
	int	*ptr;
	int	number_of_pipes;
	int	number_of_file_descriptors;

	number_of_pipes = args->total_commands - 1;

	if (args->flag_file)
		number_of_file_descriptors = (number_of_pipes * 2) + 2;
	else
		number_of_file_descriptors = number_of_pipes * 2;
	ptr = ft_calloc(number_of_file_descriptors, sizeof(int));
	if (!ptr)
		ft_shut(MEM, 0);
	return (ptr);
}

/** EXECUTION : /pipex file1 command1 command2 file2
 * The program will mimic the behaviour of '|' in shell.
 * 1. Parser arguments.
 * 2. Execute pipe and fork main process.
 * 3. Child process will.
 * 4. Parent process will read command and write it to file. */
int	main(int argc, char *argv[], char *envp[])
{
	int			fd[2];
	int			identifier;
	t_arguments	*args;
	int status;
	int fd_read;
	
	args = NULL;
	if (!parser(argc, argv))
		ft_shut(ARG, 0);
	args = arg_reader(argc, argv, envp);
	args->file_descriptors = arg_descriptors(args);
	if (pipe(fd) == -1)
		ft_shut(MSG, 0);
	identifier = fork();
	if (identifier == 0)
		first_son(fd, args);
	else if (identifier > 0)
	{
		wait(&status);
		while (args->total_commands - 2)
		{
			if (args->total_commands == 3)
				fd_read = fd[0];
			close(fd[1]);
			args->total_commands--;
			fd_read = mid_process(fd_read, args);
		}
		parent_continues(fd_read, args);
	}
	else
		ft_shut("Error at fork creation\n", 0);
		
	ft_clean(args);
	exit(0);
}


//push swap mil numeros + wc

//cat | cat | ls
	//wait(status); Si esta fuera hara todo simutaneo. es como funciona bash
	//si estuvies ddentro, es cuando en cada proceso espera.