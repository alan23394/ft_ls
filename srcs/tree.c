/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 00:05:47 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/16 02:20:02 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_binarytree	*new_item(const char *item)
{
	t_binarytree	*leaf;

	leaf = (t_binarytree *)malloc(sizeof(t_binarytree));
	leaf->string = (char *)item;
	leaf->left = 0;
	leaf->right = 0;
	return (leaf);
}

void			print_tree(t_binarytree *files)
{
	if (files->left)
	{
		print_tree(files->left);
	}
	if (files)
		ft_printf("%s\n", files->string);
	if (files->right)
	{
		print_tree(files->right);
	}
}

void			insert_tree(t_binarytree *files, const char *insert,
					int (*compare)(const char *str1, const char *str2))
{
	while (files)
	{
		if (compare(insert, files->string) >= 0)
		{
			if (files->right == 0)
			{
				files->right = new_item(insert);
				break;
			}
			else
				files = files->right;
		}
		else
		{
			if (files->left == 0)
			{
				files->left = new_item(insert);
				break;
			}
			else
				files = files->left;
		}
	}
}

void			insert_tree_reverse(t_binarytree *files, const char *insert,
					int (*compare)(const char *str1, const char *str2))
{
	while (files)
	{
 		if ((compare(insert, files->string) * -1) >= 0)
		{
			if (files->right == 0)
			{
				files->right = new_item(insert);
				break;
			}
			else
				files = files->right;
		}
		else
		{
			if (files->left == 0)
			{
				files->left = new_item(insert);
				break;
			}
			else
				files = files->left;
		}
	}
}

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
