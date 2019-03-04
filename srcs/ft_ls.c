/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 05:51:15 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/23 19:27:43 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "printing.h"
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

t_binarytree	*load_tree(t_binarytree *dirtree, t_flags *flags, int *bad_acc)
{
	DIR				*dir_p;
	struct dirent	*dir_ent;
	t_binarytree	*files;

	dir_p = opendir(T_DIR(dirtree)->name);
	if (!dir_p)
	{
		*bad_acc = 1;
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

static void		print_error(char *folder, char *error)
{
	char	*last_part_of_path;

	last_part_of_path = ft_strrchr(folder, '/') + 1;
	ft_printfd(2, "ft_ls: %s: %s\n", last_part_of_path, error);
}

void			recurse_dirs(t_binarytree *dirs, t_flags *flags)
{
	t_binarytree	*folder;
	char			*error;
	int				bad_acc;

	if (dirs->left)
		recurse_dirs(dirs->left, flags);
	folder = 0;
	error = 0;
	bad_acc = 0;
	folder = load_tree(dirs, flags, &bad_acc);
	if (bad_acc)
		error = strerror(errno);
	if (g_check_print_separator)
		ft_putchar('\n');
	if (g_check_print_dirname)
		ft_printf("%s:\n", T_DIR(dirs)->name);
	if (bad_acc)
		print_error(T_DIR(dirs)->name, error);
	else
	{
		if (F_LONG(flags->options) && T_DIR(dirs)->total_size != 0)
			ft_printf("total %lu\n", T_DIR(dirs)->total_size);
		print_dir(T_DIR(dirs), folder, flags);
	}
	g_check_print_separator = 1;
	g_check_print_dirname = 1;
	ft_treedel(&folder, delete_file);
	if (dirs->right)
		recurse_dirs(dirs->right, flags);
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
				insert_file(&files, new_file(ft_strdup(*params), *params, 0),
						compare);
		}
		else
			insert_bad(&bad, *params, strerror(errno));
		++params;
	}
	if (bad || dirs->left || dirs->right)
		g_check_print_dirname = 1;
	ft_treeiter_ltor(bad, print_bad);
	ft_treedel(&bad, delete_bad);
	ft_treeiter_ltor(files, print_file);
	ft_treedel(&files, delete_file);
	return (dirs);
}
