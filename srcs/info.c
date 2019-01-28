/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 07:49:12 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/22 15:45:00 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

# define SIX_MONTHS_SECONDS (15778476)

static char		*get_rights(struct stat stats)
{
	char			*rights;
	unsigned int	bits;
	int				i;

	rights = ft_strdup("-rwxrwxrwx");
	bits = (stats.st_mode) & (S_IRWXU | S_IRWXG | S_IRWXO);
	i = 0;
	while (i < 9)
	{
		if (!(bits & (1 << i)))
			rights[i] = '-';
		++i;
	}
	return (rights);
}

static char		*get_date(struct stat stats)
{
	char	*date;

	date = ctime(&stats.st_mtime);
	if ((time(NULL) - stats.st_mtime) > SIX_MONTHS_SECONDS)
		ft_sprintf(&date, "%-8.6s%.4s", date + 4, date + 20);
	else
		ft_sprintf(&date, "%.12s", date + 4);
	return (date);
}

void			get_info(t_file *file, char *path)
{
	struct stat		stats;

	if (lstat(path, &stats))
		return ;
	file->rights = get_rights(stats);
	file->links = stats.st_nlink;
	file->user = (getpwuid(stats.st_uid))->pw_name;
	file->group = (getgrgid(stats.st_gid))->gr_name;
	file->bytes = stats.st_size;
	file->date = get_date(stats);
}
