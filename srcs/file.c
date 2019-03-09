/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 00:05:47 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/09 02:02:27 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "libft.h"

/*
** This function, by default, sets the name variable in the file struct to be a
** pointer to the path variable: if it has multiple path components, it sets it
** to the last part of the path; if it does not, it sets it to the beginning.
*/

t_file			*new_file(char *path_to_file)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	file->name = get_name_from_path(path_to_file);
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

/*
** This function sets the name variable to be the same as the path.
**
** The reason it exists is because my printing functions print from the name
** variable of a file, and in certain cases I want the name to be the full path
** (when the file was grabbed from the command line, for instance).
*/

t_file			*new_file_full_name(char *path_to_file)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	file->name = path_to_file;
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

/*
** Never delete file->name, as it should be a pointer to some spot on the
** file->path variable.
*/

void			delete_file(t_file *file)
{
	if (file)
	{
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

/*
** This function returns a pointer to the last component of the path
** First set name to the last /
** If there wasn't a /, ft_strrchr will return 0
** If it didn't return 0, move name after the /
** If it did return zero, set it to the path
** Return name
*/

char			*get_name_from_path(char *path)
{
	char	*name;

	name = ft_strrchr(path, '/');
	if (name)
	{
		name += 1;
	}
	else
	{
		name = path;
	}
	return (name);
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
