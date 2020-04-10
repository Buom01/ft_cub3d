/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 15:10:39 by badam             #+#    #+#             */
/*   Updated: 2020/04/10 23:04:16 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	freeup_textblock(char **textblock)
{
	char **textblockcpy;

	textblockcpy = textblock;
	while (*textblockcpy)
		free( *(textblockcpy++) );
	free(textblock);
}
