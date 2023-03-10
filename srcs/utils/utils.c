/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 15:10:39 by badam             #+#    #+#             */
/*   Updated: 2020/07/20 17:15:32 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	freeup_textblock(char **textblock)
{
	char **textblockcpy;

	textblockcpy = textblock;
	while (*textblockcpy)
		free(*(textblockcpy++));
	free(textblock);
}
