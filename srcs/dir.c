/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 05:46:31 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/21 17:36:37 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dir.h"
#include "file.h"
#include "libft.h"

t_dir	*new_dir(char *new_dirname)
{
	t_dir	*dir;

	dir = (t_dir *)malloc(sizeof(t_dir));
	dir->name = new_dirname;
	dir->user_maxlen = 0;
	dir->group_maxlen = 0;
	dir->links_maxlen = 0;
	dir->size_maxlen = 0;
	dir->total_size = 0;
	dir->tv_sec = 0;
	dir->tv_nsec = 0;
	return (dir);
}

void	delete_dir(t_dir *dir)
{
	if (dir)
	{
		if (dir->name)
		{
			ft_strdel(&(dir->name));
		}
		ft_memdel((void **)&dir);
	}
}

void	insert_dir(t_binarytree **dirs, t_dir *new_dir, int (*compare)())
{
	if (!*dirs)
	{
		*dirs = ft_treenew(new_dir);
	}
	else
	{
		if (compare(new_dir, T_DIR(*dirs)) >= 0)
		{
			insert_dir(&(*dirs)->right, new_dir, compare);
		}
		else
		{
			insert_dir(&(*dirs)->left, new_dir, compare);
		}
	}
}

void	print_dir(t_dir *dir, t_binarytree *files, void (*print)())
{
	if (files)
	{
		if (files->left)
			print_dir(dir, files->left, print);
		print(T_FILE(files), dir);
		if (files->right)
			print_dir(dir, files->right, print);
	}
}
