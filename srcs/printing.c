/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:16:52 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/03 19:45:58 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printing.h"
#include "file.h"
#include "dir.h"
#include "flags.h"
#include "libftprintf.h"

void	print_dir(t_dir *dir, t_binarytree *files, t_flags *flags)
{
	if (files)
	{
		if (files->left)
			print_dir(dir, files->left, flags);
		flags->print(T_FILE(files), dir);
		if (files->right)
			print_dir(dir, files->right, flags);
	}
}

#define COLOR_NORM "\e[m"

void			print_file(t_file *file)
{
	if (file)
	{
		ft_printf("%s\n", file->name);
	}
}

void			print_file_color(t_file *file)
{
	if (file)
	{
		ft_printf("%s%s%s\n", file->color, file->name, COLOR_NORM);
	}
}

void			print_file_long(t_file *file, t_dir *dir)
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
				ft_printf("%s  %*u %-*s  %-*s  %*lu %s %s -> %s\n",
						file->rights, dir->links_maxlen, file->links,
						dir->user_maxlen, file->user, dir->group_maxlen,
						file->group, dir->bytes_maxlen, file->bytes, file->date,
						file->name, link);
			}
		}
		else
			ft_printf("%s  %*u %-*s  %-*s  %*lu %s %s\n",
					file->rights, dir->links_maxlen, file->links,
					dir->user_maxlen, file->user, dir->group_maxlen,
					file->group, dir->bytes_maxlen, file->bytes, file->date,
					file->name);
	}
}

void			print_file_long_color(t_file *file, t_dir *dir)
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
				ft_printf("%s  %*u %-*s  %-*s  %*lu %s %s%s%s -> %s\n",
						file->rights, dir->links_maxlen, file->links,
						dir->user_maxlen, file->user, dir->group_maxlen,
						file->group, dir->bytes_maxlen, file->bytes, file->date,
						file->color, file->name, COLOR_NORM, link);
			}
		}
		else
			ft_printf("%s  %*u %-*s  %-*s  %*lu %s %s%s%s\n",
					file->rights, dir->links_maxlen, file->links,
					dir->user_maxlen, file->user, dir->group_maxlen,
					file->group, dir->bytes_maxlen, file->bytes, file->date,
					file->color, file->name, COLOR_NORM);
	}
}
