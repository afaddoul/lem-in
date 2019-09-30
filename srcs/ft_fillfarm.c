/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fillfarm.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 13:44:04 by afaddoul          #+#    #+#             */
/*   Updated: 2019/09/30 19:23:45 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static void     noderm(t_dlist *lst)
{
	t_dlist *to_del;

	to_del = lst->head;
	lst->head = lst->head->next;
	ft_memdel(&to_del->content);
	ft_memdel((char**)&to_del);
}

t_farm			*ft_farmfill(t_farm *farm, t_dlist *lst)
{
	if (!(get_ants(farm, lst->head->content)))
		return (NULL);
	noderm(lst);
	if (!(lst = ft_getrooms(farm, lst)))
		return (NULL);
	//	if (!(get_edges(farm, lst)))
	//		return (NULL);
	return (farm);
}
