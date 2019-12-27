/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smouzdah <smouzdah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/04 10:46:47 by afaddoul          #+#    #+#             */
/*   Updated: 2019/12/26 23:19:58 by smouzdah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

# define MAX_FLOW 0
# define UPDATED  1
# define PRINT   -1
# define ERROR   -2

//score managing in BFS

static void dummy_del(void *content)
{
	ft_memdel((void **)(&content));
}

void			ft_revflowmark(t_room *room, int value)
{
	t_element	*tmp;

	tmp = room->edges->head;
	while (tmp)
	{
		if (((t_room*)(tmp->content))->index == value)
		{
			if (room->index == ((t_room*)(tmp->content))->flow)
				((t_room*)(tmp->content))->flow = -1;
			else
				((t_room*)(tmp->content))->flow = value;
		}
		tmp = tmp->next;
	}
}

void			ft_flowmark(t_room *room, int value)
{
	t_element	*tmp;

	tmp = room->edges->head;
	while (tmp)
	{
		if (((t_room*)(tmp->content))->index == value)
		{
			if (((t_room*)(tmp->content))->flow == value)
				((t_room*)(tmp->content))->flow = -1;
			else
				((t_room*)(tmp->content))->flow = room->index;
		}
		tmp = tmp->next;
	}
}

void 			ft_hashmapupdate(t_farm *farm, t_dlist *path)
{
	t_element 	*current;

	current = path->tail;
	ft_flowmark(GET_ENTRY(farm->start->index), ((t_item*)(current->content))->index);
	ft_revflowmark(GET_ENTRY(((t_item*)(current->content))->index), farm->start->index);
	while ((((t_item*)(current->content))->index) != farm->end->index)
	{
		farm->rooms_ht->entries[(((t_item*)(current->content))->index)]->flow = 1;
		ft_flowmark(GET_ENTRY(((t_item*)(current->content))->index), (((t_item*)(current->prev->content))->index));
		ft_revflowmark(GET_ENTRY(((t_item*)(current->prev->content))->index), (((t_item*)(current->content))->index));
		current = current->prev;
	}
	/*	size_t i = 0;
		while (i < farm->rooms_ht->size)
		{
		printf("\nFLOW:%d|", farm->rooms_ht->entries[i]->flow);
		printf(  "HT_key:%s\n|", farm->rooms_ht->entries[i]->key);
		printf(  "HT_index:%zu\n|", i);
		while ((((t_room*)(farm->rooms_ht->entries[i]->content))->edges)->head)
		{
		printf("---->FLOW:%d", ((t_room*)(((((t_room*)(farm->rooms_ht->entries[i]->content))->edges)->head)->content))->flow);
		printf("--->key:%s\n", ((t_room*)(((((t_room*)(farm->rooms_ht->entries[i]->content))->edges)->head)->content))->key);
		printf("--->key:%p\n", ((t_room*)(((((t_room*)(farm->rooms_ht->entries[i]->content))->edges)->head)->content)));

		(((t_room*)(farm->rooms_ht->entries[i]->content))->edges)->head = (((t_room*)(farm->rooms_ht->entries[i]->content))->edges)->head->next;
		}
		i++;
		}
		exit(0);*/
}

int 			ft_scorecompute(int path, int node, int ants)
{
	float		result;
	int			ret_val;

	result = ((float)(node + ants) / path);
	ret_val = (int)result;
	ret_val += (result - ret_val != 0.0f ? 1 : 0);
	return (ret_val);
}


int 			ft_prev(t_dlist *lst_vis, int target)
{
	t_element *tmp;

	tmp = lst_vis->head;
	while (tmp)
	{
		if (((t_item*)(tmp->content))->index == target)
			return (((t_item*)(tmp->content))->prev);
		tmp = tmp->next;
	}
	return (-1);
}

int				ft_pathextract(t_farm *farm, t_dlist *lst_vis, t_dlist *standby, int i_grp, int dequeued)
{
	t_dlist 	*path;
	t_item 		*item;
	t_element	*elm;
	long long	ret;

	standby = NULL;
	path = ft_dlstnew();
	if (!path)
		return (ERROR);
	item = ft_itemnew(farm->end->index, -1);
	elm  = ft_elemnew((t_item*)item);
	ft_dlstpush(path, elm);
	//printf("hehe\n");
	while (dequeued != farm->start->index)
	{
		item = ft_itemnew(dequeued, -1);
		elm  = ft_elemnew((t_item*)item);
		ft_dlstpush(path, elm);
		dequeued = ft_prev(lst_vis, dequeued);
	}
	farm->grps[i_grp].node_nb += (path->size - 1);
	ret = ft_scorecompute(farm->grps[i_grp].path_nb + 1, farm->grps[i_grp].node_nb, farm->ants);
	//printf("score is %lld\n", ret);
	if (ret < farm->grps[i_grp].score)
	{
		farm->grps[i_grp].score = ret;
		ft_hashmapupdate(farm, path);
		farm->grps[i_grp].path[farm->grps[i_grp].path_nb++] = path;
		ft_dlstdel(&lst_vis, dummy_del);
		return (UPDATED);
	}
	ft_dlstdel(&lst_vis, dummy_del);
	return (PRINT);
}

int 		ft_flowextract(t_farm *farm, t_dlist *vis, int dequeued)
{
	t_dlist 	*path;
	t_item 		*item;
	t_element	*elm;

	path = ft_dlstnew();
	if (!path)
		return (ERROR);
	item = ft_itemnew(farm->end->index, -1);
	elm  = ft_elemnew((t_item*)item);
	ft_dlstpush(path, elm);
	while (dequeued != farm->start->index)
	{
		item = ft_itemnew(dequeued, -1);
		elm  = ft_elemnew((t_item*)item);
		ft_dlstpush(path, elm);
		dequeued = ft_prev(vis, dequeued);
	}
	elm = path->head;
	while (elm)
	{
		//printf("KEY%s\n", (GET_ENTRY((t_item*)((elm->content)->index)))->key);
		elm = elm->next;
	}
	ft_hashmapupdate(farm, path);
	return (0);
}

int			ft_search_item(t_dlist *lst, int target)
{
	t_element 	*tmp;

	tmp = lst->head;
	while (tmp)
	{
		if ((((t_item*)(tmp->content))->index) == target)
			return (1);
		tmp = tmp->next;
	}
	return (0);
}

int 			ft_bfs(t_farm *farm, int i_grp)
{
	t_dlist		*queue;
	t_dlist 	*lst_vis;
	t_item		*item;
	int			dequeued;
	int 		current_item;
	t_element	*tmp;

	if (!(queue = ft_dlstnew()))
		return (ERROR);
	if (!(lst_vis = ft_dlstnew()))
		return (ERROR);
	item = ft_itemnew(farm->start->index, -1);
	ft_enqueue(queue, ft_elemnew((t_item*)item));
	ft_dlstpush(lst_vis, ft_elemnew((t_item*)ft_itemnew(farm->start->index, -1)));
	while (queue->size)
	{
		dequeued = ft_dequeue(queue);
		tmp = (((t_room*)(farm->rooms_ht->entries[dequeued]->content))->edges)->head;
		//printf("max flow dequeued %s\n", GET_ENTRY(dequeued)->key);
		while (tmp)
		{
			current_item = ((t_room*)(tmp->content))->index;
			if (current_item == farm->end->index)
			{
				//	ft_dlstdel(&queue, dummy_del); prblm here seg
				//printf("room found %s\n", GET_ENTRY(dequeued)->key);
				return (ft_pathextract(farm, lst_vis, NULL, i_grp, dequeued));
			}
			if (!ft_search_item(lst_vis, current_item) && !(farm->rooms_ht->entries[current_item]->flow))
			{
				item = ft_itemnew(current_item, dequeued);
				ft_enqueue(queue, ft_elemnew((t_item*)item));
				ft_dlstpush(lst_vis, ft_elemnew((t_item*)ft_itemnew(current_item, dequeued)));
			}
			tmp = tmp->next;
		}
	}
	ft_dlstdel(&lst_vis, dummy_del);
	return (MAX_FLOW);
}

int 			ft_flowvalid(t_farm *farm, t_dlist *lst, int flow, int target)
{
	t_element 	*tmp;

	tmp = (((t_room*)(farm->rooms_ht->entries[target]->content))->edges)->head;
	if (flow == target)
		return (0);
	while (tmp)
	{
		if (((t_room*)(tmp->content))->flow == ((t_room*)(tmp->content))->index)
		{
			if (((t_room*)(tmp->content))->flow == flow)
				return (2);
			if (ft_search_item(lst,((t_room*)(tmp->content))->index))
				return (1);
			else
				return (0);
		}
		tmp = tmp->next;
	}
	return (1);
}

int 			ft_maxflow(t_farm *farm)
{
	t_dlist		*queue;
	t_dlist 	*lst_vis;
	t_item		*item;
	int 		dequeued;
	int 		current_item;
	int 		ret;
	t_element	*tmp;

	if (!(queue = ft_dlstnew()))
		return (ERROR);
	if (!(lst_vis = ft_dlstnew()))
		return (ERROR);
	item = ft_itemnew(farm->start->index, -1);
	ft_enqueue(queue, ft_elemnew((t_item*)item));
	ft_dlstpush(lst_vis, ft_elemnew((t_item*)ft_itemnew(farm->start->index, -1)));
	while (queue->size)
	{
		dequeued = ft_dequeue(queue);
		printf("max flow dequeued %s\n", GET_ENTRY(dequeued)->key);
		tmp = (((t_room*)(farm->rooms_ht->entries[dequeued]->content))->edges)->head;
		while (tmp)
		{
			current_item = ((t_room*)(tmp->content))->index;
			if ((current_item == farm->end->index) && ((t_room*)(tmp->content))->flow == -1)
			{
				//ft_dlstdel(&queue, dummy_del);   < prblm herey
				printf("room found %s\n", GET_ENTRY(dequeued)->key);
				return (ft_flowextract(farm, lst_vis, dequeued));
			}
			if (!ft_search_item(lst_vis, current_item) && current_item != farm->end->index)
			{
				if ((ret = ft_flowvalid(farm, lst_vis, ((t_room*)(tmp->content))->flow, dequeued)) != 0)
				{
					printf("room queued %s\n", GET_ENTRY(current_item)->key);
					item = ft_itemnew(current_item, dequeued);
					ft_dlstpush(lst_vis, ft_elemnew((t_item*)ft_itemnew(current_item, dequeued)));
					ft_enqueue(queue, ft_elemnew((t_item*)item));
				}
			}
			if (ret == 2)
				break ;
			tmp = tmp->next;
		}
	}
	//printf("no more maxflow lol\n");
	//ft_dlstdel(&lst_vis, dummy_del);
	return (MAX_FLOW);
}

t_dlist			**ft_grpnew(size_t size)
{
	t_dlist		**grp;

	grp = (t_dlist**)ft_memalloc(sizeof(t_dlist*) * (int)size);
	if (!grp)
		return (NULL);
	return (grp);
}
/*
static void 		ft_farmreset(t_farm *farm)
{
	t_element 		*tmp;
	size_t i;

	i	= 0;
	while (i < farm->rooms_ht->size)
	{
		farm->rooms_ht->entries[i]->flow = 0;
		tmp = (((t_room*)(farm->rooms_ht->entries[i]->content))->edges)->head;
		while (tmp)
		{
			((t_room*)(tmp->content))->flow = -1;
			tmp = tmp->next;
		}
		i++;
	}
}
*/
static int 			ft_pathdel(t_dlist *path)
{
	if (path)
		ft_dlstdel(&path, dummy_del);
	else
		return (0);
	return (1);
}

void			ft_grpdestroy(t_dlist **grp, int path_nb)
{
	int			i;

	i = 0;
	while (i < path_nb)
		ft_pathdel(grp[i++]);
}

void			ft_grpsreverse(t_farm *farm)
{
	farm->grps[0].score = farm->grps[1].score;
	ft_grpdestroy(farm->grps[0].path, farm->grps[0].path_nb);
	farm->grps[0].path_nb = farm->grps[1].path_nb;
	farm->grps[0].path = farm->grps[1].path;
	farm->grps[1].path = ft_grpnew(farm->start->edges->size);
	farm->grps[1].path_nb = 0;
	farm->grps[1].score = 9223372036854775807;
	farm->grps[1].node_nb = 0;
}

int				ft_maxflowcaller(t_farm *farm)
{
	ft_maxflow(farm);
	exit(0);

}
int 			ft_bfsmanager(t_farm *farm)

{
	int 		ret;

	farm->grps[0].score = 9223372036854775807;
	farm->grps[0].path = ft_grpnew(GET_ENTRY(((t_room*)(farm->start))->index)->edges->size);
	while ((ret = ft_bfs(farm, 0)) != MAX_FLOW)
	{
		if (ret == ERROR)
			return (0);
		else if (ret == PRINT)
			return (1);
	}
	farm->grps[1].path = ft_grpnew(farm->start->edges->size);
	farm->grps[1].score = 9223372036854775807;
	while ((ret = ft_maxflowcaller(farm)) != 0)
	{
		if(ret == -1)
			return (0);
		if (farm->grps[0].score <= farm->grps[1].score)
		{
			//printf("im here witch score %lld and %lld\n", farm->grps[0].score , farm->grps[1].score);
			//printf("scores are %lld and %lld\n", farm->grps[0].score , farm->grps[1].score );
			//exit(1);
			return (1);
		}
		else
		{
			ft_grpsreverse(farm);
		}
	}
	//compare scores
	return (1);
}
