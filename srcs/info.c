/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 07:49:12 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/14 16:27:09 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define SIX_MONTHS_SECONDS (15778476)

/*
** The file mode printed under the -l option consists of the entry type, owner
** permissions, and group permissions.  The entry type character describes the
** type of file, as follows:
**
** 		b	Block special file
** 		c	Character special file
** 		d	Directory
** 		l	Symbolic link
** 		s	Socket link
** 		p	FIFO
** 		-	Regular file
**
** The next three fields are three characters each: owner permissions, group
** permissions, and other permissions.  Each field has three character
** positions:
**
** 		1.	If r, the file is readable; if -, it is not readable.
**
** 		2.	If w, the file is writable; if -, it is not writable.
**
** 		3.	The first of the following that applies:
**
** 			S	If in the owner permissions, the file is not executable
** 				and set-user-ID mode is set.  If in the group permissions, the
** 				file is not executable and set-group-ID mode is set.
**
** 			s	If in the owner permissions, the file is executable and
** 				set-user-ID mode is set.  If in the group permissions, the file
** 				is executable and setgroup-ID mode is set.
**
** 			x	The file is executable or the directory is searchable.
**
** 			-	The file is neither readable, writable, executable, nor
** 				set-user-ID nor set-group-ID mode, nor sticky.	(See below.)
**
** 			These next two apply only to the third character in the last group
** 			(other permissions).
**
** 			T	The sticky bit is set (mode 1000), but not execute or
** 				search permission.	(See chmod(1) or sticky(8).)
**
** 			t	The sticky bit is set (mode 1000), and is searchable or
** 				executable.  (See chmod(1) or sticky(8).)
*/

static char		type_letter(int mode)
{
	char	mode_char;

	if (S_ISBLK(mode))
		mode_char = 'b';
	if (S_ISCHR(mode))
		mode_char = 'c';
	if (S_ISDIR(mode))
		mode_char = 'd';
	if (S_ISLNK(mode))
		mode_char = 'l';
	if (S_ISSOCK(mode))
		mode_char = 's';
	if (S_ISFIFO(mode))
		mode_char = 'p';
	if (S_ISREG(mode))
		mode_char = '-';
	return (mode_char);
}

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
			rights[9 - i] = '-';
		++i;
	}
	rights[0] = type_letter(stats.st_mode);
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

void			get_file_info(t_file *file, char *path_to_file)
{
	struct stat		stats;

	// TODO make sure leaving here doesn't cause problems when deleting files
	if (lstat(path_to_file, &stats))
		return ;
	file->rights = get_rights(stats);
	file->links = stats.st_nlink;
	file->user = ft_strdup((getpwuid(stats.st_uid))->pw_name);
	file->group = ft_strdup((getgrgid(stats.st_gid))->gr_name);
	file->bytes = stats.st_size;
	file->date = get_date(stats);
	file->blocks = stats.st_blocks;
	file->tv_sec = stats.st_mtimespec.tv_sec;
	file->tv_nsec = stats.st_mtimespec.tv_nsec;
}
