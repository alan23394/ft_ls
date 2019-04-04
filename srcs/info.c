/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 07:49:12 by abarnett          #+#    #+#             */
/*   Updated: 2019/04/04 15:20:30 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info.h"
#include "file.h"
#include "flags.h"
#include "colors.h"
#include "ft_printf.h"
#include <sys/stat.h>
#include <time.h>

static char		*get_file_date(struct stat *stats)
{
	char	*date;

	date = ctime(&(stats->st_mtime));
	if ((time(NULL) - stats->st_mtime) > SIX_MONTHS_SECONDS)
		ft_sprintf(&date, "%-8.6s%.4s", date + 4, date + 20);
	else
		ft_sprintf(&date, "%.12s", date + 4);
	return (date);
}

static char		*get_size_majmin_nbr(struct stat *stats)
{
	char	*maj_min_nbrs;

	if (S_ISBLK(stats->st_mode) || S_ISCHR(stats->st_mode))
	{
		ft_sprintf(&maj_min_nbrs, "%3d, %3d",
				MAJ(stats->st_rdev), MIN(stats->st_rdev));
	}
	else
	{
		ft_sprintf(&maj_min_nbrs, "%lu", stats->st_size);
	}
	return (maj_min_nbrs);
}

int				get_file_info(t_file *file, int options, int link)
{
	struct stat		stats;

	if (options & (OP_COLOR | OP_LONG | OP_RECUR | OP_TIME | FLAG_CLI))
	{
		if ((link ? lstat(file->path, &stats) : stat(file->path, &stats)) != 0)
			return (-1);
		if (options & (OP_COLOR | OP_LONG | OP_RECUR | FLAG_CLI))
			file->rights = get_rights(&stats);
		if (options & (OP_COLOR))
			file->color = get_color(file);
		if (options & (OP_LONG))
		{
			file->ex_attr = get_extended_attributes(file->path);
			file->links = stats.st_nlink;
			file->user = get_file_user(&stats);
			file->group = get_file_group(&stats);
			file->size = get_size_majmin_nbr(&stats);
			file->date = get_file_date(&stats);
			file->blocks = stats.st_blocks;
		}
		if (options & (OP_TIME))
			get_time(file, &stats);
	}
	return (0);
}
