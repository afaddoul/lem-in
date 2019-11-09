/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afaddoul <afaddoul@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/30 09:41:11 by afaddoul          #+#    #+#             */
/*   Updated: 2019/10/15 17:49:54 by afaddoul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "lem_in.h"

void 		ft_error(void)
{
	write(1, "ERROR\n", 6);
}

int			main(void)
{
	t_farm		*farm;

	farm = ft_farmnew();
	if (!(ft_parsedata(farm)))
	{
		ft_memdel((void**)(&farm));
		ft_error();
	}
	return (0);
}
