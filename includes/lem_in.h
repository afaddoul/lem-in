/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybahlaou <ybahlaou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/21 11:42:47 by afaddoul          #+#    #+#             */
/*   Updated: 2019/10/07 09:06:27 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include "get_next_line.h"
# include <stdio.h>
# include <stdlib.h>

typedef struct			s_room
{
	char			*key;
	long long 		hash_code;
	t_dlist			*edges;
}				t_room;

typedef struct			s_farm
{
	long long		ants;
	t_dlist			*rooms;
	t_room			*start;
	t_room			*end;
	t_hashtable		*rooms_ht;
}				t_farm;

t_farm				*ft_farmfill(t_farm *farm, t_dlist *lst);
int				ft_getants(t_farm *farm, char *line);
t_dlist				*read_input(void);
int			ft_parsedata(t_farm *farm);
void				ft_error(void);
t_farm				*ft_farmnew(void);
int				get_ants(t_farm *farm, char *line);
int				ft_isnumber(char *str);
int				ft_isoverflow(char *str);
t_element			*ft_getrooms(t_farm *farm, t_dlist *lst);
t_room				*ft_roomnew(const char *name);
t_room				*ft_roomparse(const char *input);
t_hashtable			*ft_dlisttoht(t_farm *farm);
int				ft_edgesparse(const char *input,
			char **vertex, char **neighbor);
t_farm				*ft_getedges(t_farm *farm, t_element *lst);
int				ft_edgesparse(const char *input,
			char **vertex, char **neighbor);

#endif
