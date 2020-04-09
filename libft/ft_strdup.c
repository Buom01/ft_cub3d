/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 17:17:02 by badam             #+#    #+#             */
/*   Updated: 2019/11/05 17:48:50 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stdlib.h"
#include "ft_strlen.h"

char	*ft_strdup(const char *s1)
{
	size_t	strlen;
	char	*strdup;
	size_t	strdupcur;

	strlen = ft_strlen(s1) + 1;
	if (!(strdup = malloc(strlen * sizeof(char))))
		return (NULL);
	strdupcur = 0;
	while (strdupcur < strlen)
	{
		strdup[strdupcur] = s1[strdupcur];
		strdupcur++;
	}
	return (strdup);
}
