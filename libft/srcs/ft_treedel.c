/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treedel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 00:16:22 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/22 16:00:32 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binarytree.h"

/*
** Function for deleting a single node from a binary tree, using a function
** pointer to a delete function. The function should be written to take a void
** pointer to the tree's content, and it should free all memory within the void
** pointer. Then, ft_memdel is used on the node pointer, since it won't be
** referenced after this.
*/

static void		ft_treedelone(t_binarytree **node, void (*del)())
{
	if (*node)
	{
		del((*node)->content);
		ft_memdel((void **)node);
	}
}

/*
** Function for deleting a tree. It deletes first the left, and then the right,
** and then the current node. Each node is deleted with the ft_treedelone
** function, which uses the del function pointer to delete the content inside
** the tree.
*/

void			ft_treedel(t_binarytree **tree, void (*del)())
{
	if (*tree)
	{
		if ((*tree)->left)
		{
			ft_treedel(&(*tree)->left, del);
		}
		if ((*tree)->right)
		{
			ft_treedel(&(*tree)->left, del);
		}
		ft_treedelone(tree, del);
	}
}
