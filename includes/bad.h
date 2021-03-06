/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:17:50 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/01 15:19:15 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BAD_H
# define BAD_H

typedef struct s_binarytree	t_binarytree;

typedef struct	s_bad
{
	char		*name;
	char		*errormsg;
}				t_bad;

t_bad			*new_bad(char *bad_name, char *errormsg);
void			print_bad(t_bad *bad);
void			insert_bad(t_binarytree **bad_items, char *bad_name,
					char *error);
void			delete_bad(t_bad *bad);

#endif
