/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   macro.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/08 21:59:42 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 02:29:41 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#ifndef MACRO_H
# define MACRO_H

# define ARRLEN(arr) 		(sizeof(arr) / sizeof(*arr))
# define STRLEN(str) 		(ARRLEN(str) - 1)
# define PRINT(fl, str)		(write(fl, str, STRLEN(str)))
# define PRINTCHAR(fl, c)	(write(fl, &(c), 1))

# define IS_PLAYER(entity)	(entity >= MAP_PLAYER_N && entity <= MAP_PLAYER_W)

#endif
