/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treenew.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 22:59:57 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/22 07:33:54 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binarytree.h"
#include <stdlib.h>

/*
** stdlib for malloc
*/

t_binarytree	*ft_treenew(void *item)
{
	t_binarytree	*leaf;

	leaf = (t_binarytree *)malloc(sizeof(t_binarytree));
	leaf->content = item;
	leaf->left = 0;
	leaf->right = 0;
	return (leaf);
}
