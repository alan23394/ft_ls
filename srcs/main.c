/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:25:08 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/23 07:28:42 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include "ft_string.h"
#include "ft_printf.h"

int		print_illegal_option(char illegal_op)
{
	ft_printfd(2,
		"ft_ls: illegal option -- %c\nusage: ft_ls [-%s] [file ...]\n",
		illegal_op, ALL_OPTIONS);
	return (1);
}

int		main(int argc, char **argv)
{
	t_flags			flags;
	t_binarytree	*dirs;

	(void)argc;
	flags.options = get_options(&argv);
	if (flags.options == -1)
		return (print_illegal_option(**argv));
	flags.compare = get_cmp_function(flags.options);
	flags.print = get_print_func(flags.options);
	dirs = 0;
	if (*argv)
		dirs = get_dirs(argv, &flags);
	else
		insert_dir(&dirs, new_dir(ft_strdup(".")), flags.compare);
	if (dirs)
	{
		recurse_dirs(dirs, &flags);
		//ft_treedel(dirs, delete_dir);
	}
	return (0);
}
