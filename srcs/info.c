/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 07:49:12 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/22 08:32:08 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include "ft_printf.h"

# define SECONDS_IN_A_YEAR (15778476)

typedef struct			s_dir
{
	char				*path;
	unsigned int		username_len;
	unsigned int		groupname_len;
	unsigned int		links_len;
	unsigned int		bytes_len;
}						t_dir;

static char		*get_rights(struct stat stats)
{
	char			*rights;
	unsigned int	bits;
	int				i;

	i = 10;
	bits = (stats.st_mode) & (S_IRWXU | S_IRWXG | S_IRWXO);
	rights = ft_strdup("-rwxrwxrwx");
	while (--i >= 0)
		if (!((bits >> i) & 1))
			rights[9 - i] = '-';
	return (rights);
}

static char		*get_date(struct stat stats)
{
	char	*date;

	date = ctime(&stats.st_mtime);
	if ((time(NULL) - stats.st_mtime) > SECONDS_IN_A_YEAR)
		ft_sprintf(&date, "%-8.6s%.4s", date + 4, date + 20);
	else
		ft_sprintf(&date, "%.12s", date + 4);
//		date = ft_crop(&(date), 4, 12);
	return (date);
}

void			get_info(t_file *file, char *path)
{
	struct stat		stats;

	if (lstat(path, &stats))
		return ;
	file->rights = get_rights(stats);
	file->links = stats.st_nlink;
	file->username = (getpwuid(stats.st_uid))->pw_name;
	file->groupname = (getgrgid(stats.st_gid))->gr_name;
	file->bytes = stats.st_size;
	file->date = get_date(stats);
	file->name = (ft_strrchr(path, '/')) ? ft_strrchr(path, '/') : path;
	file->path = path;
}

void			print_info(t_file file)
{
//	ft_printf("%s%*d%-*s%-*s%*d%*s%s\n", "rights", stats.st_nlink,
//		(getpwuid(stats.st_uid))->pw_name, (getgrgid(stats.st_gid))->gr_name,
//		stats.st_size, ctime(&(stats.st_mtime)), path);
	ft_printf("|%s| ", file.rights);
	ft_printf("|%d| ", file.links);
	ft_printf("|%s| ", file.username);
	ft_printf("|%s| ", file.groupname);
	ft_printf("|%d| ", file.bytes);
	ft_printf("|%s| ", file.date);
	ft_printf("|%s| ", file.name);
	ft_printf("\n");
}
