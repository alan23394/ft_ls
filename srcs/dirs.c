/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 05:46:31 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/29 18:28:59 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dirs.h"
#include "libft.h"

t_dir	*new_dir(char *new_dirname)
{
	t_dir	*dir;

	dir = (t_dir *)malloc(sizeof(t_dir));
	dir->name = new_dirname;
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

void	delete_dir(t_dir *dir)
{
	if (dir)
	{
		ft_strdel(&(dir->name));
		ft_memdel((void **)&dir);
	}
}
