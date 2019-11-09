/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_farmfill.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/28 13:44:04 by afaddoul          #+#    #+#             */
/*   Updated: 2019/10/15 17:34:56 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_farm			*ft_farmfill(t_farm *farm, t_dlist *lst)
{
	t_element	*current;
	t_element	*tmp;

	if (!(ft_getants(farm, lst->head->content)))
		return (NULL);

	printf("%lld\n\n", farm->ants);

	if (!(current = ft_getrooms(farm, lst)))
		return (NULL);
	tmp = farm->rooms->head;;
	while (tmp)
	{
		printf("%s\n", ((char*)((t_room*)((t_element*)(tmp))->content)->key));
		tmp = tmp->next;
	}
	printf("\n");

	if (!(farm->rooms_ht = ft_dlisttoht(farm)))
		return (NULL);

	size_t  i = 0;
	while (i < farm->rooms_ht->size)
	{
		printf("index:%zu, room:%s index:%lld\n", i, farm->rooms_ht->entries[i]->key,
		((t_room*)(farm->rooms_ht->entries[i]->content))->index);
		i++;
	}

	//exit(0);
	if (!(ft_getedges(farm, current)))
		return (NULL);
	return (farm);
}
