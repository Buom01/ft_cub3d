/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surfaces.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <badam@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/29 23:33:41 by badam             #+#    #+#             */
/*   Updated: 2020/07/14 23:14:08 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t		surfaces_len(t_surface *surfs)
{
	register size_t	lstlen;

	lstlen = 0;
	if (surfs)
	{
		lstlen++;
		while ((surfs = surfs->next))
			lstlen++;
	}
	return (lstlen);
}

static void	swap_surfaces(t_surface **a, t_surface **b)
{
	t_surface	*tmp;
	void		*tmpnext;

	tmp = *a;
	*a = *b;
	*b = tmp;
	tmpnext = (*a)->next;
	(*a)->next = (*b)->next;
	(*b)->next = tmpnext;
}

void		surfaces_sort(t_surface **surfs)
{
	register size_t		i;
	register size_t		j;
	register t_surface	**current;

	i = surfaces_len(*surfs);
	while (i-- > 1)
	{
		j = 0;
		current = surfs;
		while (j++ <= i - 1)
		{
			if ((*current)->cache.distance >
						((t_surface*)(*current)->next)->cache.distance)
				swap_surfaces(current, (t_surface**)(&(*current)->next));
			current = (t_surface**)(&((*current)->next));
		}
	}
}
