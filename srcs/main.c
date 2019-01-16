/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:25:08 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/16 01:58:01 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

#define ALL_FLAGS "alrRt"
#define F_ALL(f) (f & 0x1)
#define F_LONG(f) (f & 0x2)
#define F_REV(f) (f & 0x4)
#define F_RECUR(f) (f & 0x8)
#define F_TIME(f) (f & 0x10)

t_binarytree	*load_tree(char *dir_str, int flags,
			int (*compare)(const char *str1, const char *str2))
{
	DIR				*dir_p;
	struct dirent	*dir_ent;
	t_binarytree	*files;

	files = 0;
	dir_p = opendir(dir_str);
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

void			ft_ls(int flags, char **folders)
{
	t_binarytree	*folder;

	folder = 0;
	if (*folders == 0)
	{
		folder = load_tree(".", flags, ft_strcmp);
		print_tree(folder);
	}
	else
	{
		while (*folders)
		{
			folder = load_tree(*folders, flags, ft_strcmp);
			print_tree(folder);
			++folders;
		}
	}
}

char	**get_flags_ls(int *flags, char **argv)
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
