/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/16 05:46:31 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/21 22:44:45 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dir.h"
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
	dir->tv_sec = 0;
	dir->tv_nsec = 0;
	return (dir);
}

void	insert_dir(t_binarytree **dirs, t_dir *new_dir, int (*compare)())
{
	if (!*dirs)
	{
		*dirs = ft_treenew(new_dir);
	}
	else
	{
		if (ft_ccount(new_dir->name, '/') > ft_ccount(T_DIR(*dirs)->name, '/'))
		{
			insert_dir(&(*dirs)->left, new_dir, compare);
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
}

void	delete_dir(t_dir *dir)
{
	if (dir)
	{
		ft_strdel(&(dir->name));
		ft_memdel((void **)&dir);
	}
}