/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 05:46:31 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/13 13:47:37 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*new_dir(char *new_dirname)
{
	t_dir	*dir;

	dir = (t_dir *)malloc(sizeof(t_dir));
	dir->name = new_dirname;
	dir->files = 0;
	dir->user_maxlen = 0;
	dir->group_maxlen = 0;
	dir->links_maxlen = 0;
	dir->bytes_maxlen = 0;
	dir->total_size = 0;
	return (dir);
}

void	insert_dir(t_binarytree **dirs, char *new_dirname,
			int (*compare)(char *s1, char *s2))
{
	if (!*dirs)
	{
		*dirs = ft_treenew(new_dir(new_dirname));
	}
	else
	{
		if (compare(new_dirname, T_DIR(*dirs)->name) >= 0)
		{
			insert_dir(&(*dirs)->right, new_dirname, compare);
		}
		else
		{
			insert_dir(&(*dirs)->left, new_dirname, compare);
		}
	}
}

void	print_dir(t_dir *dir, t_flags *flags)
{
	t_binarytree *files;

	files = dir->files;
	if (files)
	{
		if (files->left)
			print_dir(dir, files->left);
		flags->print(dir);
		if (files->right)
			print_dir(dir, files->right);
	}
}

void	delete_dir(t_dir *dir)
{
	if (dir)
	{
		ft_strdel(&(dir->name));
		ft_memdel((void **)&dir);
	}
}
