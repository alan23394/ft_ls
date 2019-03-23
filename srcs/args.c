/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/08 21:59:01 by alan              #+#    #+#             */
/*   Updated: 2019/03/23 07:16:37 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "file.h"
#include "info.h"
#include "args.h"
#include "ft_string.h"
#include <errno.h>

/*
** sort incoming parameters into trees
** put files into a directory with a files tree
** put directories into the starting directory tree
** put bad folders into a bad tree to print alphabetically
*/

void	process_arg(char *arg, t_args *trees, t_flags *flags, t_dir *files_dir)
{
	t_file	*file;
	t_dir	*dir;

	file = new_file_full_name(ft_strdup(arg));
	if (get_file_info(file, (flags->options | FLAG_CLI),
			(flags->options & OP_LONG)) == -1)
	{
		insert_bad(&trees->bad, arg, strerror(errno));
		delete_file(file);
		return ;
	}
	if (F_LONG(flags->options))
		update_dir(files_dir, file);
	if (file->rights[0] == 'd')
	{
		dir = new_dir(ft_strdup(arg));
		dir->tv_sec = file->tv_sec;
		dir->tv_nsec = file->tv_nsec;
		insert_dir(&(trees->dirs), dir, flags->compare);
		delete_file(file);
	}
	else
		insert_file(&trees->files, file, flags->compare);
}
