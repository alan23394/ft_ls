/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:25:08 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/07 18:31:53 by alan             ###   ########.fr       */
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
	int			(*func)();
	static int	(*funcs[0x20])() =
	{
		[0] = ft_strcmp,
		[OP_REV] = ft_strcmp_rev
		//funcs[OP_TIME] = cmp_time;
		//funcs[OP_REV | OP_TIME] = cmp_time_rev;
	};

	//func = funcs[F_REV(flags) | F_TIME(flags)];
	func = funcs[F_REV(flags)];
	return (func);
}

typedef void	(*print_func)();

print_func		get_print_func(int flags)
{
	void		(*func)();
	static void	(*funcs[0xF])() =
	{
		[0] = print_file,
		[OP_LONG] = print_file_long
	};

	func = funcs[F_LONG(flags)];
	return (func);
}

void			ft_ls(t_flags *flags, char **folders)
{
	t_binarytree	*dirs;

	flags->compare = get_sort_function(flags->options);
	flags->print = get_print_func(flags->options);
	dirs = 0;
	if (*folders)
		dirs = get_dirs(folders, flags->compare);
	else
		insert_dir(&dirs, ".", flags->compare);
	if (dirs)
		print_dirs(dirs, flags);
}

static char		**get_options_ls(int *options, char **argv)
{
	char	*all_options;
	char	*cur;
	int		i;

	*options = 0;
	all_options = ALL_OPTIONS;
	while ((*options != -1) && *(++argv) && (*argv[0] == '-'))
	{
		i = 1;
		if (ft_strequ(*argv, "--"))
			return (++argv);
		while (((*argv)[i]) && (*options != -1))
		{
			cur = ft_strchr(all_options, (*argv)[i]);
			*options = (cur) ? (*options | (1 << (cur - all_options))) : -1;
			++i;
		}
	}
	if (*options == -1)
		ft_printf("-%c is no good\n", (*argv)[i - 1]);
	// TODO fix that segfault
	//ft_printf("-%s is no good\n", (*argv)[i - 1]);
	return (argv);
}

int				main(int argc, char **argv)
{
	t_flags			flags;

	(void)argc;
	// make get_flags_ls return flags
	argv = get_options_ls(&flags.options, argv);
	if (flags.options == -1)
		return (-1);
	ft_ls(&flags, argv);
	return (0);
}
