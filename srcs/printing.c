/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:16:52 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/16 16:37:56 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	print_file(t_file *file)
{
	if (file)
	{
		ft_printf("%s\n", file->name);
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
			// TODO figure out what to do if this doesn't work
			if (size_of_link != -1)
			{
				link[size_of_link] = 0;
				ft_printf("%s  %*u %-*s  %-*s  %*lu %s %s -> %s\n",
						file->rights, dir->links_maxlen, file->links,
						dir->user_maxlen, file->user, dir->group_maxlen,
						file->group, dir->bytes_maxlen, file->bytes,
						file->date, file->name, link);
			}
		}
		else
			ft_printf("%s  %*u %-*s  %-*s  %*lu %s %s\n",
					file->rights, dir->links_maxlen, file->links,
					dir->user_maxlen, file->user, dir->group_maxlen,
					file->group, dir->bytes_maxlen, file->bytes,
					file->date, file->name, link);
	}
}
