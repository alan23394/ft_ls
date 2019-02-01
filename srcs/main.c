/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:25:08 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/01 14:24:02 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
** This function needs a typedef because it returns a function pointer, and
** apparently you need to use a typedef to return a function pointer.
*/

typedef int		(*sort_func)();

sort_func		get_sort_function(int flags)
{
	int	(*funcs[0x20])();
	int	(*func)();

	funcs[0] = ft_strcmp;
	funcs[F_REV(0xFF)] = ft_strcmp_rev;
	//funcs[F_TIME(0xFF)] = cmp_time;
	//funcs[F_REV(0xFF) | F_TIME(0xFF)] = cmp_time_rev;
	//func = funcs[F_REV(flags) | F_TIME(flags)];
	func = funcs[F_REV(flags)];
	return (func);
}

typedef void	(*print_func)();

print_func		get_print_func(int flags)
{
	void (*funcs[0xF])();
	void (*func)();

	funcs[0] = print_file;
	funcs[F_LONG(0xF)] = print_file_long;
	func = funcs[F_LONG(flags)];
	return (func);
}

void			ft_ls(int flags, char **folders)
{
	int				(*compare)();
	void			(*print)();
	t_binarytree	*dirs;

	compare = get_sort_function(flags);
	print = get_print_func(flags);
	dirs = 0;
	if (*folders)
		dirs = get_dirs(folders, compare);
	else
		insert_dir(&dirs, ".", compare);
	if (dirs)
		print_dirs(dirs, flags, compare, print);
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
