/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:25:08 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/16 08:46:56 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_binarytree	*load_tree(char *dir_str, int flags, int (*compare)())
{
	DIR				*dir_p;
	struct dirent	*dir_ent;
	t_binarytree	*files;

	files = 0;
	dir_p = opendir(dir_str);
	if (!dir_p)
		return (0);
	while ((dir_ent = readdir(dir_p)) != 0)
	{
		if (!F_ALL(flags) && dir_ent->d_name[0] == '.')
			continue;
		if (!files)
		{
			files = new_item(ft_strdup(dir_ent->d_name));
			continue;
		}
		if (F_REV(flags))
			insert_tree_reverse(files, ft_strdup(dir_ent->d_name), compare);
		else
			insert_tree(files, ft_strdup(dir_ent->d_name), compare);
	}
	closedir(dir_p);
	return (files);
}

void			print_dirs(t_dirtree *dirs, int flags, int (*compare)())
{
	t_binarytree	*folder;

	folder = 0;
	if (dirs->left)
		print_dirs(dirs->left, flags, compare);
	folder = load_tree(dirs->dirname, flags, compare);
	if (!folder)
	{
		ft_printfd(2, "ft_ls: %s: Not a file or directory", dirs->dirname);
	}
	else
	{
		print_tree(folder);
		delete_tree(&folder);
	}
	if (dirs->right)
		print_dirs(dirs->right, flags, compare);
}

/*
** sort incoming folders into a directory tree
** put bad folders into a bad tree to print alphabetically
*/

t_dirtree		*get_dirs(char **folders, int (*compare)())
{
	t_dirtree		*dirs;
	t_binarytree	*bad_dirs;
	struct stat		stats;

	dirs = 0;
	bad_dirs = new_item("in_function");
	if (!folders)
	{
		insert_dir(&dirs, ".", compare);
	}
	else
	{
		while (*folders)
		{
			if (stat(*folders, &stats) == 0 && S_ISDIR(stats.st_mode))
				insert_dir(&dirs, *folders, compare);
			else
				insert_tree(bad_dirs, *folders, compare);
			++folders;
		}
	}
	return (dirs);
}

typedef int		(*sort_func)();

sort_func		get_sort_function(int flags)
{
	int	(*funcs[0x20])();
	int	(*func)();

	funcs[0] = ft_strcmp;
	//funcs[F_REV(1)] = ft_strcmp_rev;
	//funcs[F_REV(1) | F_TIME(1)] = ft_timecmp_rev();
	//func = funcs[F_REV(flags) | F_TIME(flags)];
	func = funcs[F_REV(flags)];
	return (func);
}

void			ft_ls(int flags, char **folders)
{
	int				(*compare)();
	t_dirtree		*dirs;

	compare = get_sort_function(flags);
	dirs = get_dirs(folders, compare);
	print_dirs(dirs, flags, compare);
}

char			**get_flags_ls(int *flags, char **argv)
{
	char	*all_flags;
	char	*cur;
	int		i;

	*flags = 0;
	all_flags = ALL_FLAGS;
	while ((*flags != -1) && *(++argv) && (*argv[0] == '-'))
	{
		i = 1;
		if (ft_strequ(*argv, "--"))
			return (++argv);
		while (((*argv)[i]) && (*flags != -1))
		{
			cur = ft_strchr(all_flags, (*argv)[i]);
			*flags = (cur) ? (*flags | (1 << (cur - all_flags))) : -1;
			++i;
		}
	}
	if (*flags == -1)
		ft_printf("-%c is no good\n", (*argv)[i - 1]);
	// TODO fix that segfault
	//ft_printf("-%s is no good\n", (*argv)[i - 1]);
	return (argv);
}

int				main(int argc, char **argv)
{
	int				flags;

	(void)argc;
	argv = get_flags_ls(&flags, argv);
	if (flags == -1)
		return (-1);
	ft_ls(flags, argv);
	return (0);
}
