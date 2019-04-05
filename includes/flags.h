/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 21:20:13 by abarnett          #+#    #+#             */
/*   Updated: 2019/04/04 18:23:05 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLAGS_H
# define FLAGS_H

# define ALL_OPTIONS "aGlrRt1"

/*
** These are the bit values for the ls flags (OP for option). When you insert
** new ones, prefer alphabetical order, and make sure the values increase by
** powers of 2.
**
** The values are used as indexes for a function pointer array. It is set up
** like this to allow the easy combination of flags, for things like -tr, when
** you need a specific function to sort by reverse time.
*/

enum OPS {
	OP_ALL = 0x1,
	OP_COLOR = 0x2,
	OP_LONG = 0x4,
	OP_REV = 0x8,
	OP_RECUR = 0x10,
	OP_TIME = 0x20,
	OP_ONE = 0x40,
	FLAG_CLI = 0x80,
};

typedef struct	s_flags
{
	enum OPS	options;
	int			(*compare)();
	void		(*print)();
}				t_flags;

enum OPS		get_options(char ***argv);
void			*get_cmp_function(int flags);
void			*get_print_func(int flags);

#endif
