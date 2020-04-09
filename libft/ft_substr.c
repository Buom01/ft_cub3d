/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/01 17:46:03 by badam             #+#    #+#             */
/*   Updated: 2020/04/09 03:22:36 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*strcpy;
	size_t	newlen;
	char	*substr;
	char	*substrcpy;

	if (!s)
		return (NULL);
	strcpy = (char*)s;
	while (start-- && *strcpy)
		strcpy++;
	newlen = ft_strlen(strcpy);
	if (newlen > len)
		newlen = len;
	if (!(substr = malloc((newlen + 1) * sizeof(char))))
		return (NULL);
	substrcpy = substr;
	while (newlen--)
		*(substr++) = *(strcpy++);
	*substr = '\0';
	return (substrcpy);
}
