/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:25:08 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/03 19:45:01 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

int				main(int argc, char **argv)
{
	t_flags			flags;
	t_binarytree	*dirs;

	(void)argc;
	flags.options = get_options(&argv);
	if (flags.options == -1)
		return (-1);
	flags.compare = get_cmp_function(flags.options);
	flags.print = get_print_func(flags.options);
	dirs = 0;
	if (*argv)
		dirs = get_dirs(argv, flags.compare);
	else
		insert_dir(&dirs, new_dir(ft_strdup(".")), flags.compare);
	if (dirs)
	{
		recurse_dirs(dirs, &flags);
		//ft_treedel(dirs, delete_dir);
	}
	return (0);
}
