/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_treeiter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 00:30:16 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/22 07:39:47 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_binarytree.h"

/*
** Run function f on each item in the tree, moving from left to right
*/

void			ft_treeiter_ltor(t_binarytree *tree, void (*f)())
{
	if (tree)
	{
		if (tree->left)
		{
			ft_treeiter_ltor(tree->left, f);
		}
		f(tree->content);
		if (tree->right)
		{
			ft_treeiter_ltor(tree->right, f);
		}
	}
}

/*
** Run function f on each item in the tree, moving from right to left
*/

void			ft_treeiter_rtol(t_binarytree *tree, void (*f)())
{
	if (tree)
	{
		if (tree->right)
		{
			ft_treeiter_ltor(tree->left, f);
		}
		f(tree->content);
		if (tree->left)
		{
			ft_treeiter_ltor(tree->right, f);
		}
	}
}
