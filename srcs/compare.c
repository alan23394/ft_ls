/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/28 05:27:05 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/09 15:53:35 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int		cmp_name(t_cmp *c1, t_cmp *c2)
{
	char	*s1;
	char	*s2;

	s1 = c1->name;
	s2 = c2->name;
	while (s1 && s2 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	if (*s1 == '/')
		return (-1);
	else if (*s2 == '/')
		return (1);
	else
		return ((unsigned char)*s1 - (unsigned char)*s2);
}

int		cmp_name_rev(t_cmp *c1, t_cmp *c2)
{
	return (cmp_name(c2, c1));
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
