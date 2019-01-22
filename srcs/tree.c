/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/15 00:05:47 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/22 00:34:17 by abarnett         ###   ########.fr       */
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

t_binarytree	*load_tree(t_dirtree *dirtree, char *dir_str, int flags,
					int (*compare)())
{
	DIR				*dir_p;
	struct dirent	*dir_ent;
	t_binarytree	*files;
	struct stat		stats;
	char			*new_dname;

	files = 0;
	dir_p = opendir(dir_str);
	if (!dir_p)
		return (0);
	while ((dir_ent = readdir(dir_p)) != 0)
	{
		if (!F_ALL(flags) && dir_ent->d_name[0] == '.')
			continue;
		insert_tree(&files, ft_strdup(dir_ent->d_name), compare);
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
