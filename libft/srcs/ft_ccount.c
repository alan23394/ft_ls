/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ccount.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 21:17:29 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/21 21:17:44 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_ccount(char *str, char c)
{
	int	count;

	count = 0;
	while (*str)
	{
		if (*str == c)
			++count;
		++str;
	}
	return (count);
}
