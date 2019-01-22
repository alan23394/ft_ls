/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 05:51:15 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/22 14:02:03 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static int		check_print_dirname = 0;
static int		check_print_separator = 0;

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
	print_files(folder);
	check_print_separator = 1;
	check_print_dirname = 1;
	//delete_file(&folder);
	if (dirs->right)
		print_dirs(dirs->right, flags, compare);
}

static void		print_bad_dirs(t_binarytree *bad_dirs)
{
	if (bad_dirs)
	{
		if (bad_dirs->left)
		{
			print_bad_dirs(bad_dirs->left);
		}
		ft_printf("ft_ls: %s: No such file or directory\n",
				T_DIR(bad_dirs)->name);
		if (bad_dirs->right)
		{
			print_bad_dirs(bad_dirs->right);
		}
	}
}

/*
** sort incoming folders into a directory tree
** put bad folders into a bad tree to print alphabetically
*/

t_binarytree	*get_dirs(char **folders, int (*compare)(char *s1, char *s2))
{
	t_binarytree	*dirs;
	t_binarytree	*bad_dirs;
	struct stat		stats;

	dirs = 0;
	bad_dirs = 0;
	if (!*folders)
		insert_dir(&dirs, ".", compare);
	else
	{
		while (*folders)
		{
			if (stat(*folders, &stats) == 0 && S_ISDIR(stats.st_mode))
				insert_dir(&dirs, *folders, compare);
			else
				insert_dir(&bad_dirs, *folders, compare);
			++folders;
		}
	}
	if (bad_dirs || dirs->left || dirs->right)
		check_print_dirname = 1;
	print_bad_dirs(bad_dirs);
	return (dirs);
}
