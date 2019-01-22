/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeinsert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 00:29:03 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/22 07:38:44 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binarytree.h"

/*
** Insert into the tree based on the return of a compare function, that takes
** the content of the current node and the void pointer being inserted as
** arguments. If the function returns >= 0, the item is inserted to the right,
** and it is inserted to the left if the function returns less than 0. An
** example of this, is holding a string in the void*, and using ft_strcmp to
** compare them. Then the tree will be sorted alphabetically. This
** implementation allows for bigger things though, like storing entire structs
** in the void pointer and comparing only specific elements of those structs.
*/

void			ft_treeinsert(t_binarytree **tree, void *insert,
					int (*compare)())
{
	if (!*tree)
	{
		*tree = ft_treenew(insert);
	}
	else
	{
		if (compare(insert, (*tree)->content) >= 0)
		{
			ft_treeinsert(&(*tree)->right, insert, compare);
		}
		else
		{
			ft_treeinsert(&(*tree)->left, insert, compare);
		}
	}
}
