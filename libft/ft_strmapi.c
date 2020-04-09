/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/03 20:22:07 by badam             #+#    #+#             */
/*   Updated: 2019/11/10 22:11:20 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "stddef.h"
#include "ft_strlen.h"
#include "ft_substr.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	strlen;
	char	*fstr;
	char	*fstrcpy;

	if (!s || !f)
		return (NULL);
	strlen = ft_strlen(s);
	fstr = ft_substr(s, 0, strlen + 1);
	if (!fstr)
		return (NULL);
	fstrcpy = fstr;
	while (*fstrcpy)
	{
		*fstrcpy = f((unsigned int)(fstrcpy - fstr), (char)(*fstrcpy));
		fstrcpy++;
	}
	return (fstr);
}
