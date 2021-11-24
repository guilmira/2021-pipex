/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:12:15 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/24 12:56:44 by guilmira         ###   ########.fr       */
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
# define MEM "Failed memory allocation.\n"
# define ARG "Incorrect arguments.\n"
# define MSG "Pipe function failure.\n"
# define FILE_ERROR "File not found or error at opening.\n"
# define DUP_ERROR "Dup2 function failure.\n"
typedef struct s_command
{
	char	**command1;
	char	**command2;
	char	*path1;
	char	*path2;
	char	*file_input;
	char	*file_output;
}			t_command;

/* PARSER */
int		parser(int argc, char *argv[]);
int		prepare_process(int fd_to_close, int fd_to_prepare);
/* PARENT PROCESS */
int		process_origin(int fd[2], t_command *command_list);
/* SON PROCESS */
void		process_son(int fd[2], char *path, char **command1, char *path_command);
void		second_son(int ex_read, char **command2, char *path_command, char *path_file);
/* AUXILIAR */
void	ft_shut(char *str, int i);
#endif