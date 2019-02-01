/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 05:51:15 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/31 17:18:31 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <errno.h>

static int		g_check_print_dirname = 0;
static int		g_check_print_separator = 0;

char			*get_dirname(char *cur, char *add)
{
	int		len_of_cur;
	int		len_of_add;
	char	*newdir;

	len_of_cur = ft_strlen(cur);
	len_of_add = ft_strlen(add);
	newdir = ft_strnew(len_of_cur + 1 + len_of_add);
	ft_strncpy(newdir, cur, len_of_cur);
	newdir[len_of_cur] = '/';
	ft_strncpy(newdir + len_of_cur + 1, add, len_of_add);
	return (newdir);
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
		path = get_dirname(T_DIR(dirtree)->name, dir_ent->d_name);
		insert_file(&files, new_file(ft_strdup(dir_ent->d_name), path),
				compare);
		if (F_RECUR(flags) && lstat(path, &stats) == 0 &&
				S_ISDIR(stats.st_mode))
			insert_dir(&(dirtree->right), path, compare);
		else
			ft_strdel(&path);
	}
	closedir(dir_p);
	return (files);
}

void			print_permission_denied(char *folder)
{
	char	*last_part_of_path;

	last_part_of_path = ft_strrchr(folder, '/') + 1;
	ft_printfd(2, "ft_ls: %s: Permission denied\n", last_part_of_path);
}

void			print_dirs(t_binarytree *dirs, int flags,
					int (*compare)(char *s1, char *s2))
{
	t_binarytree	*folder;

	folder = 0;
	if (dirs->left)
		print_dirs(dirs->left, flags, compare);
	folder = load_tree(dirs, flags, compare);
	if (check_print_separator)
		ft_putchar('\n');
	if (check_print_dirname)
		ft_printf("%s:\n", T_DIR(dirs)->name);
	if (folder)
		ft_treeiter_ltor(folder, print_file);
	else
		print_permission_denied(T_DIR(dirs)->name);
	check_print_separator = 1;
	check_print_dirname = 1;
	ft_treedel(&folder, delete_file);
	if (dirs->right)
		print_dirs(dirs->right, flags, compare);
}

/*
** sort incoming parameters into trees
** put files into a files tree
** put directories into the starting directory tree
** put bad folders into a bad tree to print alphabetically
*/

t_binarytree	*get_dirs(char **params, int (*compare)(char *s1, char *s2))
{
	t_binarytree	*files;
	t_binarytree	*dirs;
	t_binarytree	*bad;
	struct stat		stats;

	files = 0;
	dirs = 0;
	bad = 0;
	while (*params)
	{
		if (lstat(*params, &stats) == 0)
		{
			if (S_ISDIR(stats.st_mode))
				insert_dir(&dirs, ft_strdup(*params), compare);
			else
				insert_file(&files, new_file(ft_strdup(*params), *params),
						compare);
		}
		else
			insert_bad(&bad, *params, strerror(errno));
		++params;
	}
	if (bad || dirs->left || dirs->right)
		check_print_dirname = 1;
	ft_treeiter_ltor(bad, print_bad);
	ft_treedel(&bad, delete_bad);
	ft_treeiter_ltor(files, print_file);
	ft_treedel(&files, delete_file);
	return (dirs);
}
