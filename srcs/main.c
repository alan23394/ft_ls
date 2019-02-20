/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:25:08 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/14 16:25:57 by abarnett         ###   ########.fr       */
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
	{
		recurse_dirs(dirs, flags);
		//ft_treedel(dirs, delete_dir);
	}
}

int				get_options(char ***argv)
{
	int		options;
	char	*cur;
	int		i;

	options = 0;
	while ((options != -1) && *(++(*argv)) && (***argv == '-' && (**argv)[1]))
	{
		if (ft_strequ(**argv, "--"))
		{
			++(*argv);
			return (options);
		}
		i = 1;
		while (((**argv)[i]) && (options != -1))
		{
			cur = ft_strchr(ALL_OPTIONS, (**argv)[i]);
			options = (cur) ? (options | (1 << (cur - ALL_OPTIONS))) : -1;
			++i;
		}
	}
	if (options == -1)
		ft_printfd(2,
			"ft_ls: illegal option -- %c\nusage: ft_ls [-alrRt] [file ...]\n",
			(**argv)[i - 1]);
	return (options);
}

int				main(int argc, char **argv)
{
	t_flags			flags;

	(void)argc;
	flags.options = get_options(&argv);
	if (flags.options == -1)
		return (-1);
	ft_ls(&flags, argv);
	return (0);
}
