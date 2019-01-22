/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirtree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 05:46:31 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/22 07:16:23 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_dir	*new_dir(char *item)
{
	t_dir	*dir;

	dir = (t_dir *)malloc(sizeof(t_dir));
	dir->name = item;
	dir->files = 0;
	return (dir);
}

void	insert_dir(t_binarytree **dirs, char *insert,
			int (*compare)(char *s1, char *s2))
{
	if (!*dirs)
	{
		*dirs = ft_treenew(new_dir(insert));
	}
	else
	{
		if (compare(insert, (*dirs)->content->d_name) >= 0)
		{
			insert_dirs(&(*dirs)->right, insert, compare);
		}
		else
		{
			insert_dirs(&(*dirs)->left, insert, compare);
		}
	}
}

void	delete_dir(t_dir *dir)
{
	if (dir)
	{
		ft_strdel(&(*dir)->name);
		ft_memdel((void **)&dir);
	}
}
