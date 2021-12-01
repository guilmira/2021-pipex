/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:17:27 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/01 13:23:20 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** PURPOSE : End of the process.
 * 1. Final fork + execute last son.*/
static int	end_process(t_arguments *args)
{
	int	identifier;
	int	status;
	int	last_index;

	args->command_number++;
	last_index = (args->command_number * 2) - 2;
	identifier = fork();
	if (identifier == 0)
		last_son(last_index, args);
	else if (identifier > 0)
		wait(&status);
	else
		ft_shut(FORK_ERROR, 0);
	return (0);
}

/** PURPOSE : Executes fork function to run commands.
 * 1. Create first pipe. 
 * 2. Fork process in a loop, and inside each son process, run command.
 * 3. Continue running program until last fork. */
static void	process_exe(t_arguments *args)
{
	int	i;
	int	status;
	int	identifier;

	if (pipe(args->fds) == -1)
		ft_shut(MSG, 0);
	identifier = fork();
	if (identifier == 0)
		first_son(args);
	else if (identifier > 0)
	{
		i = -1;
		wait(&status);
		close(args->fds[1]);
		while (++i < args->total_commands - 2)
			mid_process(args);
		end_process(args);
	}
	else
		ft_shut(FORK_ERROR, 0);
}

/** EXECUTION : /pipex file1 command1 command2 file2
 * The program will mimic the behaviour of '|' in shell.
 * 1. Parser arguments.
 * 2. Read int structure
 * 3. Execcut process and clean memory */
int	main(int argc, char *argv[], char *envp[])
{
	t_arguments	*args;

	args = NULL;
	if (!parser(argc, argv))
		ft_shut(ARG, 0);
	args = arg_reader(argc, argv, envp);
	args->fds = arg_descriptors(args);
	process_exe(args);
	ft_clean(args);
	exit(0);
}

//push swap mil numeros + wc

//cat | cat | ls
	//wait(status); Si esta fuera hara todo simutaneo. es como funciona bash
	//si estuvies ddentro, es cuando en cada proceso espera.

/** PURPOSE : shutdown program freeing heap allocated memory.
 * 1. Clean memory for argument.
 * 3. Print error message. */
//void	ft_shutdown(t_time *arg)