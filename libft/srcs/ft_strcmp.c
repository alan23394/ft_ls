/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/22 11:03:49 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/17 00:55:15 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	return (ft_strncmp(s1, s2, ft_strlen(s1) + 1));
}

/*
** Does the exact same thing as regular strcmp, but returns the reverse result
** instead, for sorting reverse alphabetically.
*/

int	ft_strcmp_rev(const char *s1, const char *s2)
{
	return (ft_strncmp(s2, s1, ft_strlen(s1) + 1));
}
