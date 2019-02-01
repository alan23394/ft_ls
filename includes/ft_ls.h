/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:23:26 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/01 14:07:50 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "libftprintf.h"

/*
** libftprintf.h includes libft.h
** libft.h includes unistd.h and stdlib.h
**
** Allowed functions from unistd.h:
** readlink
** write
**
** Allowed functions from stdlib.h:
** malloc
** free
*/

# include <dirent.h>

/*
** Allowed functions from dirent.h:
** opendir
** readdir
** closdir
*/

# include <sys/stat.h>

/*
** Allowed functions from sys/stat.h:
** stat
**	stat obtains information about the file pointed to by path
**
** lstat
**	lstat does the same as stat, but for a symlink instead of the thing it
**	links to
*/

# include <sys/types.h>
# include <pwd.h>
# include <uuid/uuid.h>
# include <grp.h>

/*
** Allowed functions from those:
** getpwuid
** getgrgid
*/

# include <sys/xattr.h>

/*
** Allowed functions from sys/xattr.h:
** listxattr
** getxattr
*/

# include <time.h>

/*
** Allowed functions from time.h:
** time
** ctime
*/

# include <string.h>

/*
** Allowed functions from string.h:
** strerror
*/

# include "dirs.h"
# include "files.h"
# include "bad.h"

# define ALL_FLAGS "alrRt"
# define F_ALL(f) (f & 0x1)
# define F_LONG(f) (f & 0x2)
# define F_REV(f) (f & 0x4)
# define F_RECUR(f) (f & 0x8)
# define F_TIME(f) (f & 0x10)

char			*get_dirname(char *cur, char *add);
t_binarytree	*load_tree(t_binarytree *dirtree, int flags,
					int (*compare)(char *s1, char *s2));
void			print_dirs(t_binarytree *dirs, int flags,
					int (*compare)(char *s1, char *s2), void (*print)());

t_binarytree	*get_dirs(char **folders,
					int (*compare)(char *s1, char *s2));

#endif
