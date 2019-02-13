/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:16:52 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/13 13:39:37 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file(t_dir *dir)
{
	t_file	*file;

	file = T_FILE(dir->files);
	if (file)
	{
		ft_printf("%s\n", file->name);
	}
}

void	print_file_long(t_dir *dir)
{
	t_file	*file;
	char	link[1024];
	int		size_of_link;

	file = T_FILE(dir->files);
	if (file)
	{
		if (*file->rights == 'l')
		{
			size_of_link = readlink(file->path, link, 1023);
			if (size_of_link != -1)
			{
				link[size_of_link] = 0;
				ft_printf("%s %u %s %s %lu %s %s -> %s\n", file->rights,
						file->links, file->user, file->group, file->bytes,
						file->date, file->name, link);
			}
		}
		else
			ft_printf("%s %u %s %s %lu %s %s\n", file->rights,
					file->links, file->user, file->group, file->bytes,
					file->date, file->name);
	}
}
