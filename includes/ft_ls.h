/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:23:26 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/16 08:44:46 by abarnett         ###   ########.fr       */
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
**	int stat(const char *restrict path, struct stat *restrict buf);
**	stat obtains information about the file pointed to by path
**
** lstat
**	int lstat(const char *restrict path, struct stat *restrict buf);
**	lstat does the same as stat, but for a symbolic link
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

# include <stdio.h>

/*
** Allowed functions from stdio.h:
** perror
*/

# include <string.h>

/*
** Allowed functions from string.h:
** strerror
*/

# define ALL_FLAGS "alrRt"
# define F_ALL(f) (f & 0x1)
# define F_LONG(f) (f & 0x2)
# define F_REV(f) (f & 0x4)
# define F_RECUR(f) (f & 0x8)
# define F_TIME(f) (f & 0x10)

typedef struct			s_binarytree
{
	char				*string;
	struct s_binarytree	*left;
	struct s_binarytree	*right;

}						t_binarytree;

t_binarytree			*new_item(const char *item);
void					print_tree(t_binarytree *files);
void					insert_tree(t_binarytree *files, const char *insert,
							int (*compare)());
void					insert_tree_reverse(t_binarytree *files,
							const char *insert, int (*compare)());
void					delete_tree(t_binarytree **tree);

typedef struct			s_dirtree
{
	char				*dirname;
	struct s_binarytree	*files;
	struct s_dirtree	*left;
	struct s_dirtree	*right;
}						t_dirtree;

t_dirtree				*new_dir(const char *item);
void					insert_dir(t_dirtree **dirs, const char *insert,
							int (*compare)());

#endif
