/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 00:05:47 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/21 22:50:35 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "info.h"
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
	file->bytes = 0;
	file->date = 0;
	file->blocks = 0;
	file->tv_sec = 0;
	file->tv_nsec = 0;
	get_file_info(file, path_to_file);
	return (file);
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

void			delete_file(t_file *file)
{
	if (file)
	{
		ft_strdel(&(file->name));
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
