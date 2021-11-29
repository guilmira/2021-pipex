/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   0type.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 11:23:53 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/29 11:48:38 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** PURPOSE : Searchs on arguments for '<' symbol. */
static int file_symbol_detected(char *str)
{
	int i;

	i = -1;
	while(str[++i])
	{
		if (str[i] == '<' && (str[i + 1] == ' ' || !str[i + 1]))
		{
			if (i == 0)
				return (1);
			else if (i != 0)
			{
				str[i - 1] = ' ';
				return (1);
			}
		}
	}
	return (0);
}

/** PURPOSE : Does the path of the command exist? Returns bool. */
int file_exists(char *str)
{
	int fp;
	
	fp = open(str, O_RDONLY);
	if (fp == -1)
		return (0);
	close(fp);
		return (1);
}

/** PURPOSE : Is a file being introudced as an input to the program? */
int	file_detector(int argc, char *argv[])
{
	int i;
	int j;

	j = -1;
	i = -1;
	while (++i < argc)
		if (file_symbol_detected(argv[i]))
			if (file_exists(argv[i + 1]))
				return (1);
return (0);
}