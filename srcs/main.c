/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:25:08 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/14 23:55:08 by abarnett         ###   ########.fr       */
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

t_binarytree	*load_tree(char *dir_str, int reverse,
			int (*compare)(const char *str1, const char *str2))
{
	DIR				*dir_p;
	struct dirent	*dir_ent;
	t_binarytree	*files;

	files = 0;
	dir_p = opendir(dir_str);
	while ((dir_ent = readdir(dir_p)) != 0)
	{
		if (!files)
		{
			files = new_item(dir_ent->d_name);
			continue;
		}
		if (reverse)
			insert_tree_reverse(files, (const char *)dir_ent->d_name, compare);
		else
			insert_tree(files, (const char *)dir_ent->d_name, compare);
	}
	closedir(dir_p);
	return (files);
}

int				main(int argc, char **argv)
{
	t_binarytree	*folder;

	folder = 0;
	if (argc == 1)
		folder = load_tree(".", 0, ft_strcmp);
	else if (argc == 2)
		folder = load_tree(argv[1], 0, ft_strcmp);
	print_tree(folder);
	return (0);
}
