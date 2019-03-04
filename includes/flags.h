/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 21:20:13 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/03 19:28:02 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

# define ALL_OPTIONS "alrRt"

/*
** These are the bit values for the ls flags (OP for option). When you insert
** new ones, prefer alphabetical order, and make sure the values increase by
** powers of 2.
**
** The values are used as indexes for a function pointer array. It is set up
** like this to allow the easy combination of flags, for things like -tr, when
** you need a specific function to sort by reverse time. The last value is used
** as the size of the function pointer array, so make sure it is the bitwise
** addition of all of the previous flags (one power of 2 higher should always
** work).
*/

enum {
	OP_ALL = 0x1,
	OP_COLOR = 0x2,
	OP_LONG = 0x4,
	OP_REV = 0x8,
	OP_RECUR = 0x10,
	OP_TIME = 0x20,
	OP_MAX_OPS = 0x40,
};

/*
** These are a set of macros to apply a bitwise AND to the flags variable with
** the specific option. They exist to be convenient; even though they don't
** really assist much, I like using them, and I think they help produce
** readable code.
*/

# define F_ALL(f) (f & OP_ALL)
# define F_COLOR(f) (f & OP_COLOR)
# define F_LONG(f) (f & OP_LONG)
# define F_REV(f) (f & OP_REV)
# define F_RECUR(f) (f & OP_RECUR)
# define F_TIME(f) (f & OP_TIME)

typedef struct	s_flags
{
	int			options;
	int			(*compare)();
	void		(*print)();
}				t_flags;

int				get_options(char ***argv);
void			*get_cmp_function(int flags);
void			*get_print_func(int flags);

#endif
