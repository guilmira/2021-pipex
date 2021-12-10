/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:17:27 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/10 09:37:30 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** PURPOSE : End of the process.
 * 1. Final fork + execute last son. */
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
		ft_shutdown(FORK_ERROR, 0, args);
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
		ft_shutdown(MSG, 0, args);
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
		ft_shutdown(FORK_ERROR, 0, args);
}

/** EXECUTION : /pipex file1 command1 command2 file2
 * The program will mimic the behaviour of '|' in shell.
 * 1. Parser arguments.
 * 2. Read int structure.
 * 3. Execute process and clean memory. */
int	main(int argc, char *argv[], char *envp[])
{
	t_arguments	*args;

	args = NULL;
	if (!parser(argc, argv))
		ft_shut(ARG, 0);
	args = arg_reader(argc, argv, envp);
	args->fds = arg_descriptors(args);
	process_exe(args);
	free_heap_memory(args);
	exit(0);
}

//cat | cat | ls
	//wait(status); Si esta fuera hara todo simutaneo. es como funciona bash
	//si estuvies ddentro, es cuando en cada proceso espera.