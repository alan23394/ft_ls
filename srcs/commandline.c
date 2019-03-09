/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:59:01 by alan              #+#    #+#             */
/*   Updated: 2019/03/09 13:51:41 by alan             ###   ########.fr       */
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

/*
void	process_file_commandline(char *filename, t_binarytree **files,
					t_flags *flags, t_binarytree *dirtree)
{
	t_file	*file;
	t_dir	*dir;

	if (!F_ALL(flags->options) && filename[0] == '.')
		return ;
	file = new_file(filename);
	if (get_file_info(file, flags->options) == -1)
	{
		delete_file(file);
		return ;
	}
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
*/

/*
** sort incoming parameters into trees
** put files into a directory with a files tree
** put directories into the starting directory tree
** put bad folders into a bad tree to print alphabetically
*/

void	sort_commandline(char *param, t_cli *trees, int (*compare)())
{
	t_file	*tmp_file;
	t_dir	*tmp_dir;

	tmp_file = new_file_full_name(ft_strdup(param));
	if (get_file_info(tmp_file, OP_RECUR) == -1)
	{
		insert_bad(&trees->bad, param, strerror(errno));
		delete_file(tmp_file);
		return ;
	}
	if (tmp_file->rights[0] == 'd')
	{
		tmp_dir = new_dir(ft_strdup(param));
		tmp_dir->tv_sec = tmp_file->tv_sec;
		tmp_dir->tv_nsec = tmp_file->tv_nsec;
		insert_dir(&(trees->dirs), tmp_dir, compare);
		delete_file(tmp_file);
	}
	else
	{
		insert_file(&trees->files, tmp_file, compare);
	}
}
