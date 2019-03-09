/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commandline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:59:01 by alan              #+#    #+#             */
/*   Updated: 2019/03/09 15:08:36 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "info.h"
#include <errno.h>

/*
** sort incoming parameters into trees
** put files into a directory with a files tree
** put directories into the starting directory tree
** put bad folders into a bad tree to print alphabetically
*/

void	sort_commandline(char *param, t_cli *trees, t_flags *flags,
				t_dir *files_dir)
{
	t_file	*file;
	t_dir	*dir;

	file = new_file_full_name(ft_strdup(param));
	if (get_file_info(file, flags->options) == -1)
	{
		insert_bad(&trees->bad, param, strerror(errno));
		delete_file(file);
		return ;
	}
	if (F_LONG(flags->options))
		update_dir(files_dir, file);
	if (file->rights[0] == 'd')
	{
		dir = new_dir(ft_strdup(param));
		dir->tv_sec = file->tv_sec;
		dir->tv_nsec = file->tv_nsec;
		insert_dir(&(trees->dirs), dir, flags->compare);
		delete_file(file);
	}
	else
		insert_file(&trees->files, file, flags->compare);
}
