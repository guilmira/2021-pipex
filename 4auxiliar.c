/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   4auxiliar.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilmira <guilmira@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 11:04:00 by guilmira          #+#    #+#             */
/*   Updated: 2021/11/22 13:38:36 by guilmira         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/** PURPOSE : Output error with given value 1, close the program.
 * If exit signal is 0, it will prevent the appeareance of message:
 * "make: *** [exe] Error 1" */
void	ft_shut(char *str, int i)
{
	write(1, str, ft_strlen(str));
	exit(i);
}
