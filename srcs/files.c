/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 00:05:47 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/22 14:07:15 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_file			*new_file(char *filename)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	file->name = filename;
	file->rights = 0;
	file->user = 0;
	file->group = 0;
	file->date = 0;
	file->links = 0;
	file->bytes = 0;
	return (file);
}

void			print_files(t_binarytree *files)
{
	if (files)
	{
		if (files->left)
		{
			print_files(files->left);
		}
		ft_printf("%s\n", T_FILE(files)->name);
		if (files->right)
		{
			print_files(files->right);
		}
	}
}

void			insert_file(t_binarytree **files, char *insert,
					int (*compare)(char *s1, char *s2))
{
	if (!*files)
	{
		*files = ft_treenew(new_file(insert));
	}
	else
	{
		if (compare(insert, T_FILE(*files)->name) >= 0)
		{
			insert_file(&(*files)->right, insert, compare);
		}
		else
		{
			insert_file(&(*files)->left, insert, compare);
		}
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

t_binarytree	*load_tree(t_binarytree *dirtree, int flags,
					int (*compare)(char *s1, char *s2))
{
	DIR				*dir_p;
	struct dirent	*dir_ent;
	t_binarytree	*files;
	char			*path;
	struct stat		stats;

	dir_p = opendir(T_DIR(dirtree)->name);
	if (!dir_p)
		return (0);
	files = 0;
	while ((dir_ent = readdir(dir_p)) != 0)
	{
		if (!F_ALL(flags) && dir_ent->d_name[0] == '.')
			continue;
		insert_file(&files, ft_strdup(dir_ent->d_name), compare);
		path = get_dirname(T_DIR(dirtree)->name, dir_ent->d_name);
		if (F_RECUR(flags) && stat(path, &stats) == 0 &&
				S_ISDIR(stats.st_mode))
			insert_dir(&(dirtree->right), path, compare);
		else
			ft_strdel(&path);
	}
	closedir(dir_p);
	return (files);
}

void			delete_file(t_file *file)
{
	(void)file;
}
