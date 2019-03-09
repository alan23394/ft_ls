/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 22:07:13 by alan              #+#    #+#             */
/*   Updated: 2019/03/08 23:41:54 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "info.h"
#include <errno.h>

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

static void		update_dir(t_dir *dir, t_file *file)
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
	temp = ft_numlen(file->bytes);
	if (temp > dir->bytes_maxlen)
		dir->bytes_maxlen = temp;
}

static void		process_file(char *filename, t_binarytree **files,
					t_flags *flags, t_binarytree *dirtree)
{
	char	*path;
	t_file	*file;
	t_dir	*dir;

	if (!F_ALL(flags->options) && filename[0] == '.')
		return ;
	path = get_dirname(T_DIR(dirtree)->name, filename);
	file = new_file(ft_strdup(filename), path);
	(void)get_file_info(file, flags->options);
	if (F_LONG(flags->options))
		update_dir(T_DIR(dirtree), file);
	insert_file(files, file, flags->compare);
	if (F_RECUR(flags->options) && file->rights[0] == 'd' &&
		!(ft_strequ(filename, ".") || ft_strequ(filename, "..")))
	{
		dir = new_dir(ft_strdup(path));
		dir->tv_sec = file->tv_sec;
		dir->tv_nsec = file->tv_nsec;
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
