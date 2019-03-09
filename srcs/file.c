/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 00:05:47 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/08 23:44:51 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "libft.h"

t_file			*new_file(char *filename, char *path_to_file)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	file->name = filename;
	file->path = path_to_file;
	file->rights = 0;
	file->links = 0;
	file->user = 0;
	file->group = 0;
	file->date = 0;
	file->bytes = 0;
	file->blocks = 0;
	file->color = 0;
	file->tv_sec = 0;
	file->tv_nsec = 0;
	return (file);
}

void			delete_file(t_file *file)
{
	if (file)
	{
		if (file->name)
			ft_strdel(&(file->name));
		if (file->path)
			ft_strdel(&(file->path));
		if (file->rights)
			ft_strdel(&(file->rights));
		if (file->user)
			ft_strdel(&(file->user));
		if (file->group)
			ft_strdel(&(file->group));
		if (file->date)
			ft_strdel(&(file->date));
		ft_memdel((void **)&file);
	}
}

void			insert_file(t_binarytree **files, t_file *new_file,
					int (*compare)())
{
	if (!*files)
	{
		*files = ft_treenew(new_file);
	}
	else
	{
		if (compare(new_file, T_FILE(*files)) >= 0)
		{
			insert_file(&(*files)->right, new_file, compare);
		}
		else
		{
			insert_file(&(*files)->left, new_file, compare);
		}
	}
}
