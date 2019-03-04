/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:25:08 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/21 21:39:12 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

/*
void			ft_ls(t_flags *flags, char **folders)
{
	t_binarytree	*dirs;

	dirs = 0;
	if (*folders)
		dirs = get_dirs(folders, flags->compare);
	else
		insert_dir(&dirs, new_dir(ft_strdup(".")), flags->compare);
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
