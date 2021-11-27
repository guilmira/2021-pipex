/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:12:15 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/27 13:05:24 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

/* LIBS */
# include "libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
/* DEBUGGING */
# include <stdio.h>
/* FILE PATHS */
# define PATH_BIN "/bin/"
# define PATH_USR "/usr/bin/"
# define FILE_NAME "outfile.txt"
# define FULL_PERMISSIONS 0777
# define RESTRICTED_PERM 777
/* ERROR MESSAGES */
# define ARGUMENTS 5
# define ARGUMENT_FILES 2
# define MEM "Failed memory allocation.\n"
# define ARG "Incorrect arguments.\n"
# define MSG "Pipe function failure.\n"
# define LST "Failure at linked list.\n"
# define FILE_ERROR "File not found or error at opening.\n"
# define DUP_ERROR "Dup2 function failure.\n"
# define EXE_ERROR "Execve function failure.\n"

typedef struct s_command
{
	char	*path;
	char	**command;
}			t_command;

typedef struct s_arguments
{
	t_list	*commands_lst;
	char	*file_input;
	char	*file_output;
}			t_arguments;

/* PARSER */
int			parser(int argc, char *argv[]);
char		*set_path(char *command, char **folders);
int			prepare_process(int fd_to_close, int fd_to_prepare);
/* READER */
t_arguments	*arg_reader(char *argv[], int argc, char *envp[]);
char		*set_path(char *command, char **folders);
/* PARENT PROCESS */
int			process_origin(int fd[2], t_arguments *args);
/* SON PROCESS */
void		first_son(int fd[2], t_arguments *args, int command_number);
void		last_son(int fd[2], t_arguments *args, int command_number);
/* AUXILIAR */
void		ft_shut(char *str, int i);
void		ft_clean(t_arguments *args);
#endif