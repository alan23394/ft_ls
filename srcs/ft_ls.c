/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 05:51:15 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/08 23:57:41 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "printing.h"
#include <errno.h>

static int		g_check_print_dirname = 0;
static int		g_check_print_separator = 0;

void			recurse_dirs(t_binarytree *dirs, t_flags *flags)
{
	t_binarytree	*folder;
	char			*error;

	if (dirs->left)
		recurse_dirs(dirs->left, flags);
	folder = 0;
	error = 0;
	folder = load_tree(dirs, flags, &error);
	if (g_check_print_separator)
		ft_putchar('\n');
	if (g_check_print_dirname)
		ft_printf("%s:\n", T_DIR(dirs)->name);
	if (error)
		print_error(T_DIR(dirs)->name, error);
	else
	{
		if (F_LONG(flags->options) && T_DIR(dirs)->total_size != 0)
			ft_printf("total %lu\n", T_DIR(dirs)->total_size);
		print_dir(T_DIR(dirs), folder, flags->print);
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

/*
** TODO
** make a "directory" for the command line, so the files can have proper
** spacing with -l from the command line
*/

/*
t_binarytree	*get_dirs(char **params, int (*compare)())
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
				insert_dir(&dirs, new_dir(ft_strdup(*params)), compare);
			else
				insert_file(&files, new_file(ft_strdup(*params),
						ft_strdup(*params)), compare);
		}
		else
			insert_bad(&bad, *params, strerror(errno));
		++params;
	}
	if (bad || (dirs && (dirs->left || dirs->right)))
		g_check_print_dirname = 1;
	if (files)
		g_check_print_separator = 1;
	ft_treeiter_ltor(bad, print_bad);
	ft_treedel(&bad, delete_bad);
	ft_treeiter_ltor(files, print_file);
	ft_treedel(&files, delete_file);
	return (dirs);
}
*/

t_binarytree	*get_dirs(char **params, int (*compare)())
{
	t_dir			*input_dir;
	t_file			*tmp_file;
	t_binarytree	*files;
	t_binarytree	*dirs;
	t_binarytree	*bad;
	struct stat		stats;

	input_dir = 0;
	tmp_file = 0;
	files = 0;
	dirs = 0;
	bad = 0;
	while (*params)
	{
		tmp_file = new_file(ft_strdup(param), 0);
		if (lstat(*params, &stats) == 0)
		{
			if (S_ISDIR(stats.st_mode))
				insert_dir(&dirs, new_dir(ft_strdup(*params)), compare);
			else
				insert_file(&files, new_file(ft_strdup(*params),
						ft_strdup(*params)), compare);
		}
		else
			insert_bad(&bad, *params, strerror(errno));
		++params;
	}
	if (bad || (dirs && (dirs->left || dirs->right)))
		g_check_print_dirname = 1;
	if (files)
		g_check_print_separator = 1;
	ft_treeiter_ltor(bad, print_bad);
	ft_treedel(&bad, delete_bad);
	ft_treeiter_ltor(files, print_file);
	ft_treedel(&files, delete_file);
	return (dirs);
}
