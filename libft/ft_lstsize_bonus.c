/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 16:07:34 by badam             #+#    #+#             */
/*   Updated: 2019/11/10 22:42:45 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_lstsize(t_list *lst)
{
	int	lstlen;

	lstlen = 0;
	if (lst)
	{
		lstlen++;
		while ((lst = lst->next))
			lstlen++;
	}
	return (lstlen);
}
