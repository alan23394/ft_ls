/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:16:52 by abarnett          #+#    #+#             */
/*   Updated: 2019/04/04 14:52:36 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printing.h"
#include "file.h"
#include "dir.h"
#include "flags.h"
#include "ft_printf.h"
#include <unistd.h>

#define COLOR_NORM "\e[m"

void	print_error(char *folder, char *error)
{
	char	*last_part_of_path;

	last_part_of_path = get_name_from_path(folder);
	ft_printfd(2, "ft_ls: %s: %s\n", last_part_of_path, error);
}

void	print_file(t_file *file)
{
	if (file)
	{
		ft_printf("%s\n", file->name);
	}
}

void	print_file_color(t_file *file)
{
	if (file)
	{
		ft_printf("%s%s%s\n", file->color, file->name, COLOR_NORM);
	}
}

void	print_file_long(t_file *file, t_dir *dir)
{
	char	link[1024];
	int		size_of_link;

	if (file)
	{
		if (*file->rights == 'l')
		{
			size_of_link = readlink(file->path, link, 1023);
			if (size_of_link != -1)
			{
				link[size_of_link] = 0;
				ft_printf("%s%c %*u %-*s  %-*s  %*s %s %s -> %s\n",
					file->rights, file->ex_attr, dir->links_maxlen, file->links,
					dir->user_maxlen, file->user, dir->group_maxlen,
					file->group, dir->size_maxlen, file->size, file->date,
					file->name, link);
			}
		}
		else
			ft_printf("%s%c %*u %-*s  %-*s  %*s %s %s\n",
				file->rights, file->ex_attr, dir->links_maxlen, file->links,
				dir->user_maxlen, file->user, dir->group_maxlen, file->group,
				dir->size_maxlen, file->size, file->date, file->name);
	}
}

void	print_file_long_color(t_file *file, t_dir *dir)
{
	char	link[1024];
	int		size_of_link;

	if (file)
	{
		if (*file->rights == 'l')
		{
			size_of_link = readlink(file->path, link, 1023);
			if (size_of_link != -1)
			{
				link[size_of_link] = 0;
				ft_printf("%s%c %*u %-*s  %-*s  %*s %s %s%s%s -> %s\n",
					file->rights, file->ex_attr, dir->links_maxlen, file->links,
					dir->user_maxlen, file->user, dir->group_maxlen,
					file->group, dir->size_maxlen, file->size, file->date,
					file->color, file->name, COLOR_NORM, link);
			}
		}
		else
			ft_printf("%s%c %*u %-*s  %-*s  %*s %s %s%s%s\n",
				file->rights, file->ex_attr, dir->links_maxlen, file->links,
				dir->user_maxlen, file->user, dir->group_maxlen, file->group,
				dir->size_maxlen, file->size, file->date, file->color,
				file->name, COLOR_NORM);
	}
}
