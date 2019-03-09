/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 05:51:15 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/09 13:57:00 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "printing.h"
#include "info.h"
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

t_binarytree	*get_dirs(char **params, int (*compare)())
{
	t_cli	trees;
	//t_dir	*input_dir;

	//input_dir = 0;
	trees.files = 0;
	trees.dirs = 0;
	trees.bad = 0;
	while (*params)
	{
		sort_commandline(*params, &trees, compare);
		++params;
	}
	if (trees.bad || (trees.dirs && (trees.dirs->left || trees.dirs->right)))
		g_check_print_dirname = 1;
	if (trees.files)
		g_check_print_separator = 1;
	ft_treeiter_ltor(trees.bad, print_bad);
	ft_treedel(&(trees.bad), delete_bad);
	ft_treeiter_ltor(trees.files, print_file);
	ft_treedel(&(trees.files), delete_file);
	return (trees.dirs);
}
