/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 21:21:01 by abarnett          #+#    #+#             */
/*   Updated: 2019/04/04 20:50:51 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "flags.h"
#include "printing.h"
#include "compare.h"
#include "ft_string.h"

/*
** This function updates the "base" print type. By base, I mean the print types
** that cannot conflict. For example, long printing vs single column printing
** vs horizontal vs vertical etc. This function tests the cursor against the
** ALL_OPTIONS macro, and then checks if the option fits with one of the base
** print types, and sets the base_print pointer to it if it does. If it doesn't
** match, it does nothing.
**
** It sets the base print type by checking the recieved option against a
** bitmask of base_types, and if the new option is in the base_types, it:
** and-equals the inverse of the base types
** 	this applies a 1 everywhere there isn't a base type, and applies a 0
** 	everywhere there is. this is to clear all base types already applied.
** or-equals the new option
** 	this simply applies it to the bits
*/

static void		update_print(enum e_ops *base_print, char *cursor)
{
	enum e_ops	op;
	enum e_ops	base_types;

	op = (enum e_ops)(1 << (cursor - ALL_OPTIONS));
	base_types = (OP_LONG | OP_ONE);
	if (op & base_types)
	{
		*base_print &= ~base_types;
		*base_print |= op;
	}
}

/*
** This function gets the options out of the argv string.
**
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

enum e_ops		get_options(char ***argv)
{
	enum e_ops	options;
	char		*cur;

	options = OP_ONE;
	while (options && *(++(*argv)) && (***argv == '-' && (**argv)[1]))
	{
		if (ft_strequ(**argv, "--"))
		{
			++(*argv);
			return (options);
		}
		while (*(**argv + 1) && options)
		{
			++(**argv);
			cur = ft_strchr(ALL_OPTIONS, (***argv));
			if (cur)
			{
				options = options | (1 << (cur - ALL_OPTIONS));
			}
			else
				options = 0;
			update_print(&options, cur);
		}
	}
	return (options);
}

void			*get_cmp_function(int flags)
{
	int			(*func)();
	static int	(*funcs[])() = {
		[0] = cmp_name,
		[OP_REV] = cmp_name_rev,
		[OP_TIME] = cmp_time,
		[OP_REV | OP_TIME] = cmp_time_rev,
	};

	func = funcs[flags & (OP_REV | OP_TIME)];
	return (func);
}

void			*get_print_func(int flags)
{
	void		(*func)();
	static void	(*funcs[])() = {
		[OP_ONE] = print_file,
		[OP_ONE | OP_COLOR] = print_file_color,
		[OP_LONG] = print_file_long,
		[OP_COLOR | OP_LONG] = print_file_long_color
	};

	func = funcs[flags & (OP_COLOR | OP_LONG | OP_ONE)];
	return (func);
}
