/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badam <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 17:04:05 by badam             #+#    #+#             */
/*   Updated: 2019/11/04 17:04:47 by badam            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LSTDELONE_BONUS_H
# define FT_LSTDELONE_BONUS_H

void	ft_lstdelone(t_list *lst, void (*del)(void*));

#endif
