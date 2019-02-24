/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:27:38 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/21 20:53:18 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMPARE_H
# define COMPARE_H

typedef struct		s_cmp
{
	char			*name;
	unsigned long	tv_sec;
	unsigned long	tv_nsec;
}					t_cmp;

int					cmp_name(t_cmp *c1, t_cmp *c2);
int					cmp_name_rev(t_cmp *c1, t_cmp *c2);
int					cmp_time(t_cmp *c1, t_cmp *c2);
int					cmp_time_rev(t_cmp *c1, t_cmp *c2);

#endif
