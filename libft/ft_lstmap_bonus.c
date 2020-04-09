/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/10 23:04:05 by badam             #+#    #+#             */
/*   Updated: 2019/11/12 20:42:17 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "ft_lstclear_bonus.h"
#include "ft_lstnew_bonus.h"

t_list		*ft_lstmap_free(t_list **nl, void *content, void (*del)(void *))
{
	if (content)
		del(content);
	ft_lstclear(nl, del);
	return (NULL);
}

t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstcpy;
	void	*newcnt;
	t_list	*newlst;
	t_list	*newlstcpy;

	newlst = 0;
	lstcpy = lst;
	while (lstcpy)
	{
		if (!(newcnt = f(lstcpy->content)))
			return (ft_lstmap_free(&newlst, newcnt, del));
		if (!(newlstcpy = ft_lstnew(newcnt)))
			return (ft_lstmap_free(&newlst, newcnt, del));
		if (!newlst)
			newlst = newlstcpy;
		newlstcpy = newlstcpy->next;
		lstcpy = lstcpy->next;
	}
	return (newlst);
}
