/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/15 13:12:15 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/23 13:45:51 by guilmira         ###   ########.fr       */
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
# define ARG "Incorrect arguments\n"
# define MSG "Pipe function failure\n"
# define GNL_ERROR "Problem with GNL\n"
/* PARSER */
int		parser(int argc, char *argv[]);
int		prepare_process(int fd_to_close, int fd_to_prepare);
/* PARENT PROCESS */
int		process_origin(int fd[2], char *command2, char *path_out);
/* SON PROCESS */
int		process_son(int fd[2], char *path);
int		second_son(int ex_read, char *command2, char *path_out);
/* AUXILIAR */
void	ft_shut(char *str, int i);
#endif