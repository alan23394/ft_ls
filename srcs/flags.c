/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 21:21:01 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/17 03:50:51 by abarnett         ###   ########.fr       */
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

	options = 0;
	while ((options != -1) && *(++(*argv)) && (***argv == '-' && (**argv)[1]))
	{
		if (ft_strequ(**argv, "--"))
		{
			++(*argv);
			return (options);
		}
		while (*(**argv + 1) && (options != -1))
		{
			++(**argv);
			cur = ft_strchr(ALL_OPTIONS, (***argv));
			options = (cur) ? (options | (1 << (cur - ALL_OPTIONS))) : -1;
		}
	}
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

/*
** TODO Fix magic number in array index (remove entirely)
*/

void			*get_print_func(int flags)
{
	void		(*func)();
	static void	(*funcs[7])() =
	{
		[0] = print_file,
		[OP_COLOR] = print_file_color,
		[OP_LONG] = print_file_long,
		[OP_LONG | OP_COLOR] = print_file_long_color
	};

	func = funcs[F_LONG(flags) | F_COLOR(flags)];
	return (func);
}
