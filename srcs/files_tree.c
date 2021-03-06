/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 22:07:13 by alan              #+#    #+#             */
/*   Updated: 2019/04/04 20:46:44 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "info.h"
#include "dir.h"
#include "file.h"
#include "flags.h"
#include "ft_utils.h"
#include "ft_string.h"
#include "ft_binarytree.h"
#include <dirent.h>
#include <errno.h>
#include <string.h>

/*
** string.h: strerror
*/

/*
** This function takes the old path and the new foldername and combines them,
** with a / inbetween.
**
** Fixed to make the / folder not start off with // when recursively making new
** dirs
*/

char			*get_dirname(char *cur, char *add)
{
	int		len_of_cur;
	int		len_of_add;
	char	*newdir;

	len_of_cur = ft_strlen(cur);
	len_of_add = ft_strlen(add);
	if (len_of_cur == 1 && *cur == '/')
	{
		newdir = ft_strnew(len_of_cur + len_of_add);
		newdir[0] = '/';
		ft_strncpy(newdir + 1, add, len_of_add);
	}
	else
	{
		newdir = ft_strnew(len_of_cur + 1 + len_of_add);
		ft_strncpy(newdir, cur, len_of_cur);
		newdir[len_of_cur] = '/';
		ft_strncpy(newdir + len_of_cur + 1, add, len_of_add);
	}
	return (newdir);
}

void			update_dir(t_dir *dir, t_file *file)
{
	unsigned int	temp;

	dir->total_size += file->blocks;
	temp = ft_strlen(file->user);
	if (temp > dir->user_maxlen)
		dir->user_maxlen = temp;
	temp = ft_strlen(file->group);
	if (temp > dir->group_maxlen)
		dir->group_maxlen = temp;
	temp = ft_numlen(file->links);
	if (temp > dir->links_maxlen)
		dir->links_maxlen = temp;
	temp = ft_strlen(file->size);
	if (temp > dir->size_maxlen)
		dir->size_maxlen = temp;
}

static void		process_file(char *f_name, t_binarytree **files,
					t_flags *flags, t_binarytree *dirtree)
{
	char	*path;
	t_file	*file;
	t_dir	*dir;

	if (!(flags->options & OP_ALL) && f_name[0] == '.')
		return ;
	path = get_dirname(T_DIR(dirtree)->name, f_name);
	file = new_file(path);
	if (get_file_info(file, flags->options, 1) == -1)
	{
		delete_file(file);
		return ;
	}
	if (flags->options & OP_LONG)
		update_dir(T_DIR(dirtree), file);
	insert_file(files, file, flags->compare);
	if ((flags->options & OP_RECUR) && file->rights[0] == 'd' &&
		!(f_name[0] == '.' && (!f_name[1] || (f_name[1] == '.' && !f_name[2]))))
	{
		dir = new_dir(ft_strdup(path));
		dir->tv_sec = file->tv_sec;
		dir->tv_nsec = file->tv_nsec;
		dir->subdir_level = T_DIR(dirtree)->subdir_level + 1;
		insert_dir(&(dirtree->right), dir, flags->compare);
	}
}

/*
** Things to preserve in directory struct
** total blocks
** width of longest name
**
** Things to preserve in filename struct
** name
** rights stuff?
** user name
** group name
** links
** # of bytes
** date modified
*/

t_binarytree	*load_tree(t_binarytree *dirtree, t_flags *flags, char **error)
{
	DIR				*dir_p;
	struct dirent	*dir_ent;
	t_binarytree	*files;

	dir_p = opendir(T_DIR(dirtree)->name);
	if (!dir_p)
	{
		*error = strerror(errno);
		return (0);
	}
	files = 0;
	while ((dir_ent = readdir(dir_p)) != 0)
	{
		process_file(dir_ent->d_name, &files, flags, dirtree);
	}
	closedir(dir_p);
	return (files);
}
