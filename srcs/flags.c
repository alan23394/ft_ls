/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 21:21:01 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/23 19:07:39 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags.h"
#include "printing.h"
#include "compare.h"
#include "libftprintf.h"

/*
** while ((options != -1) && *(++(*argv)) && (***argv == '-' && (**argv)[1]))
** 	if options is -1,
** 		we've hit a failure, quit
** 	*(++(*argv))
** 		first deferefence to get the double-array of strings,
** 		++ to go to the next string,
** 		second dereference to check if it exists
** 	***argv == '-' && (**argv)[1]
** 		check if the character is a -,
** 		and check if there is a character after that -
** 			this is to tell the difference between a single - (could be a
** 			directory), and the start of a flag.
*/

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

void			*get_cmp_function(int flags)
{
	int			(*func)();
	static int	(*funcs[OP_MAX_OPS])() =
	{
		[0] = cmp_name,
		[OP_REV] = cmp_name_rev,
		[OP_TIME] = cmp_time,
		[OP_REV | OP_TIME] = cmp_time_rev,
	};

	func = funcs[F_REV(flags) | F_TIME(flags)];
	return (func);
}

void			*get_print_func(int flags)
{
	void		(*func)();
	static void	(*funcs[OP_LONG + 1])() =
	{
		[0] = print_file,
		[OP_LONG] = print_file_long
	};

	func = funcs[F_LONG(flags)];
	return (func);
}
