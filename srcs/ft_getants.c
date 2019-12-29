/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_ants.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 14:09:53 by afaddoul          #+#    #+#             */
/*   Updated: 2019/12/29 20:40:41 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			ft_getants(t_farm *farm, char *line)
{
	if (!ft_isulong(line, '\0'))
		return (0);
	if (!(farm->ants = ft_atol(line)))
		return (0);
	return (1);
}
