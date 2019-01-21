/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 05:51:15 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/21 06:06:10 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int		check_print_dirname = 0;
static int		check_print_separator = 0;

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
	bad_dirs = 0;
	if (!*folders)
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
				insert_tree(&bad_dirs, *folders, compare);
			++folders;
			if (*folders)
				check_print_dirname = 1;
		}
	}
	if (bad_dirs && check_print_dirname == 0)
		check_print_dirname = 1;
	print_bad_dirs(bad_dirs);
	return (dirs);
}

void			print_dirs(t_dirtree *dirs, int flags, int (*compare)())
{
	t_binarytree	*folder;

	folder = 0;
	if (dirs->left)
		print_dirs(dirs->left, flags, compare);
	folder = load_tree(dirs, dirs->dirname, flags, compare);
	if (check_print_separator)
		ft_putchar('\n');
	if (check_print_dirname)
		ft_printf("%s:\n", dirs->dirname);
	print_tree(folder);
	if (!check_print_separator)
		check_print_separator = 1;
	if (!check_print_dirname)
		check_print_dirname = 1;
	delete_tree(&folder);
	if (dirs->right)
		print_dirs(dirs->right, flags, compare);
}

void			print_bad_dirs(t_binarytree *bad_dirs)
{
	if (bad_dirs)
	{
		if (bad_dirs->left)
		{
			print_bad_dirs(bad_dirs->left);
		}
		ft_printf("ft_ls: %s: No such file or directory\n", bad_dirs->string);
		if (bad_dirs->right)
		{
			print_bad_dirs(bad_dirs->right);
		}
	}
}
