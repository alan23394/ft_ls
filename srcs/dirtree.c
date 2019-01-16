/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirtree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 05:46:31 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/16 08:44:25 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dirtree	*new_dir(const char *item)
{
	t_dirtree	*leaf;

	leaf = (t_dirtree *)malloc(sizeof(t_dirtree));
	leaf->dirname = (char *)item;
	leaf->files = 0;
	leaf->left = 0;
	leaf->right = 0;
	return (leaf);
}

void			insert_dir(t_dirtree **dirs, const char *insert,
					int (*compare)())
{
	t_dirtree	*cur;

	if (!*dirs)
	{
		*dirs = new_dir(insert);
		return ;
	}
	cur = *dirs;
	while (cur)
	{
		if (compare(insert, cur->dirname) >= 0)
		{
			if (cur->right == 0)
			{
				cur->right = new_dir(insert);
				break ;
			}
			else
				cur = cur->right;
		}
		else
		{
			if (cur->left == 0)
			{
				cur->left = new_dir(insert);
				break ;
			}
			else
				cur = cur->left;
		}
	}
}

/*
void			delete_tree(t_binarytree **tree)
{
	if (*tree)
	{
		if ((*tree)->left)
		{
			delete_tree(&(*tree)->left);
		}
		if ((*tree)->right)
		{
			delete_tree(&(*tree)->left);
		}
		ft_strdel(&(*tree)->string);
		ft_memdel((void **)tree);
	}
}
*/
