/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 00:05:47 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/31 16:56:42 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "files.h"
#include "libftprintf.h"

t_file			*new_file(char *filename, char *path_to_file)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	file->name = filename;
	get_file_info(file, path_to_file);
	return (file);
}

void			insert_file(t_binarytree **files, t_file *new_file,
					int (*compare)(char *s1, char *s2))
{
	if (!*files)
	{
		*files = ft_treenew(new_file);
	}
	else
	{
		if (compare(new_file->name, T_FILE(*files)->name) >= 0)
		{
			insert_file(&(*files)->right, new_file, compare);
		}
		else
		{
			insert_file(&(*files)->left, new_file, compare);
		}
	}
}

void			print_file(t_file *file)
{
	if (file)
	{
		ft_printf("%s\n", file->name);
	}
}

void			delete_file(t_file *file)
{
	if (file)
	{
		ft_strdel(&(file->name));
		ft_strdel(&(file->rights));
		ft_strdel(&(file->date));
		ft_memdel((void **)&file);
	}
}
