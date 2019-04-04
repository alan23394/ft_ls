/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_rights.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 14:54:42 by abarnett          #+#    #+#             */
/*   Updated: 2019/04/04 15:25:55 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_string.h"
#include <sys/stat.h>

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

static char	type_letter(int mode)
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

char		*get_rights(struct stat *stats)
{
	char			*rights;
	unsigned int	bits;
	int				i;

	rights = ft_strdup("-rwxrwxrwx");
	bits = (stats->st_mode) & (S_IRWXU | S_IRWXG | S_IRWXO);
	i = 0;
	while (i < 9)
	{
		if (!(bits & (1 << i)))
			rights[9 - i] = '-';
		++i;
	}
	rights[0] = type_letter(stats->st_mode);
	if (S_ISUID & stats->st_mode)
		rights[3] = (rights[3] == '-') ? 'S' : 's';
	if (S_ISGID & stats->st_mode)
		rights[6] = (rights[6] == '-') ? 'S' : 's';
	if (S_ISVTX & stats->st_mode)
		rights[9] = (rights[9] == '-') ? 'T' : 't';
	return (rights);
}
