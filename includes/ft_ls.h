/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:23:26 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/16 02:19:05 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

typedef struct			s_binarytree
{
	char				*string;
	struct s_binarytree	*left;
	struct s_binarytree	*right;

}						t_binarytree;

#include "libftprintf.h"

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

#include <dirent.h>

/*
** Allowed functions from dirent.h:
** opendir
** readdir
** closdir
*/

#include <sys/stat.h>

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

#include <sys/types.h>
#include <pwd.h>
#include <uuid/uuid.h>
#include <grp.h>

/*
** Allowed functions from those:
** getpwuid
** getgrgid
*/

#include <sys/xattr.h>

/*
** Allowed functions from sys/xattr.h:
** listxattr
** getxattr
*/

#include <time.h>

/*
** Allowed functions from time.h:
** time
** ctime
*/

#include <stdio.h>

/*
** Allowed functions from stdio.h:
** perror
*/

#include <string.h>

/*
** Allowed functions from string.h:
** strerror
*/


t_binarytree	*new_item(const char *item);
void			print_tree(t_binarytree *files);
void			insert_tree(t_binarytree *files, const char *insert,
					int (*compare)(const char *str1, const char *str2));
void			insert_tree_reverse(t_binarytree *files, const char *insert,
					int (*compare)(const char *str1, const char *str2));
void			delete_tree(t_binarytree **tree);

#endif
