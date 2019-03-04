/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 05:27:05 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/22 18:38:41 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_name(t_cmp *c1, t_cmp *c2)
{
	return (ft_strcmp(c1->name, c2->name));
}

int		cmp_name_rev(t_cmp *c1, t_cmp *c2)
{
	return (ft_strcmp(c2->name, c1->name));
}

int		cmp_time(t_cmp *c1, t_cmp *c2)
{
	if (c1->tv_sec < c2->tv_sec)
		return (1);
	else if (c1->tv_sec > c2->tv_sec)
		return (-1);
	else
	{
		if (c1->tv_nsec < c2->tv_nsec)
			return (1);
		else if (c1->tv_nsec > c2->tv_nsec)
			return (-1);
		else
			return (cmp_name(c1, c2));
	}
}

int		cmp_time_rev(t_cmp *c1, t_cmp *c2)
{
	return (cmp_time(c2, c1));
}
