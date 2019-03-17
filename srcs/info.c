/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 07:49:12 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/16 22:37:29 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info.h"
#include "ft_ls.h"
#include "colors.h"

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

	if (S_ISREG(mode))
		mode_char = '-';
	else if (S_ISBLK(mode))
		mode_char = 'b';
	else if (S_ISCHR(mode))
	 	mode_char = 'c';
	else if (S_ISDIR(mode))
	 	mode_char = 'd';
	else if (S_ISLNK(mode))
	 	mode_char = 'l';
	else if (S_ISFIFO(mode))
	 	mode_char = 'p';
	else if (S_ISSOCK(mode))
		mode_char = 's';
	else
		mode_char = '?';
	return (mode_char);
}

char			get_extended_attributes(char *filename)
{
	acl_t		acl;
	acl_entry_t	dummy;
	ssize_t		xattr;

	acl = acl_get_link_np(filename, ACL_TYPE_EXTENDED);
	if (acl && acl_get_entry(acl, ACL_FIRST_ENTRY, &dummy) == -1)
	{
		acl_free(acl);
		acl = 0;
	}
	xattr = listxattr(filename, 0, 0, XATTR_NOFOLLOW);
	if (xattr < 0)
	{
		xattr = 0;
	}
	if (xattr > 0)
	{
		return ('@');
	}
	else if (acl != NULL)
	{
		return ('+');
	}
	else
	{
		return (' ');
	}
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

static void		get_time(t_file *file, struct stat stats)
{
	file->tv_sec = stats.st_mtimespec.tv_sec;
	file->tv_nsec = stats.st_mtimespec.tv_nsec;
}

int				get_file_info(t_file *file, int options, int link)
{
	struct stat		stats;

	if (options & (OP_COLOR | OP_LONG | OP_RECUR | OP_TIME))
	{
		if ((link ? lstat(file->path, &stats) : stat(file->path, &stats)) != 0)
			return (-1);
		if (options & (OP_COLOR | OP_LONG | OP_RECUR))
			file->rights = get_rights(stats);
		if (options & (OP_COLOR))
			file->color = get_color(file);
		if (options & (OP_LONG))
		{
			file->ex_attr = get_extended_attributes(file->path);
			file->links = stats.st_nlink;
			file->user = ft_strdup((getpwuid(stats.st_uid))->pw_name);
			file->group = ft_strdup((getgrgid(stats.st_gid))->gr_name);
			file->bytes = stats.st_size;
			file->date = get_date(stats);
			file->blocks = stats.st_blocks;
		}
		if (options & (OP_TIME))
			get_time(file, stats);
	}
	return (0);
}
