/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 00:05:47 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/22 07:31:03 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void			print_tree(t_binarytree *files)
{
	if (files)
	{
		if (files->left)
		{
			print_tree(files->left);
		}
		ft_printf("%s\n", files->string);
		if (files->right)
		{
			print_tree(files->right);
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

t_binarytree	*load_tree(t_binarytree *dirtree, int flags, int (*compare)())
{
	DIR				*dir_p;
	struct dirent	*dir_ent;
	struct stat		stats;
	char			*new_dname;

	dir_p = opendir(dirtree->content->d_name);
	if (!dir_p)
		return (0);
	while ((dir_ent = readdir(dir_p)) != 0)
	{
		if (!F_ALL(flags) && dir_ent->d_name[0] == '.')
			continue;
		insert_file(&files, ft_strdup(dir_ent->d_name), compare);
		new_dname = get_dirname(dirtree->dirname, dir_ent->d_name);
		if (F_RECUR(flags) && stat(new_dname, &stats) == 0 &&
				S_ISDIR(stats.st_mode))
			insert_dir(&(dirtree->right), new_dname, compare);
		else
			ft_strdel(&new_dname);
	}
	closedir(dir_p);
	return (files);
}

t_file			new_file(char *filename)
{
	t_file
}

void			insert_file(t_binarytree **files, char *insert,
					int (*compare)(char *s1, char *s2))
{
	if (!*dirs)
	{
		*dirs = ft_treenew(new_file(insert));
	}
	else
	{
		if (compare(insert, (*dirs)->content->d_name) >= 0)
		{
			insert_dirs(&(*dirs)->right, insert, compare);
		}
		else
		{
			insert_dirs(&(*dirs)->left, insert, compare);
		}
	}
}
