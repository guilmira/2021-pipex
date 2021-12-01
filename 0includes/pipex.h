/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:12:15 by guilmira          #+#    #+#             */
/*   Updated: 2021/12/01 13:23:19 by guilmira         ###   ########.fr       */
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
# define ARGUMENTS 2
# define NOT_COMMANDS 4
# define MEM "Failed memory allocation.\n"
# define ARG "Incorrect arguments.\n"
# define MSG "Pipe function failure.\n"
# define LST "Failure at linked list.\n"
# define FILE_ERROR "File not found or error at opening.\n"
# define FORK_ERROR "Error at fork creation\n"
# define DUP_ERROR "Dup2 function failure.\n"
# define EXE_ERROR "Execve function failure.\n"

/** Struct that stores command data. */
typedef struct s_command
{
	char	*path;
	char	**command;
}			t_command;

/** Struct that stores arguments and program parameters. */
typedef struct s_arguments
{
	t_list	*commands_lst;
	int		flag_file;
	int		command_number;
	int		total_commands;
	int		*fds;
	char	*file_input;
	char	*file_output;
}			t_arguments;

/* FILES */
int			file_management(int argc, char *argv[], t_arguments *args);
/* PARSER */
int			parser(int argc, char *argv[]);
char		*set_path(char *command, char **folders);
int			prepare_process(int fd_to_close, int fd_to_prepare);
/* READER */
t_arguments	*arg_reader(int argc, char *argv[], char *envp[]);
char		*set_path(char *command, char **folders);
/* PARENT PROCESS */
void		mid_process(t_arguments *args);
/* SON PROCESS */
void		first_son(t_arguments *args);
void		last_son(int index, t_arguments *args);
/* AUXILIAR */
void		ft_shut(char *str, int i);
void		ft_clean(t_arguments *args);
int			file_exists(char *str);
int			*arg_descriptors(t_arguments *args);
void		*ft_lst_position(t_list *lst, int n);

#endif