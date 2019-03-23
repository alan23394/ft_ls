/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bad.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:17:03 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/23 07:29:51 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bad.h"
#include "ft_mem.h"
#include "ft_string.h"
#include "ft_printf.h"
#include "ft_binarytree.h"

t_bad	*new_bad(char *bad_name, char *errormsg)
{
	t_bad	*bad;

	bad = (t_bad *)ft_memalloc(sizeof(t_bad));
	bad->name = bad_name;
	bad->errormsg = errormsg;
	return (bad);
}

void	print_bad(t_bad *bad)
{
	if (bad)
	{
		ft_printfd(2, "ft_ls: %s: %s\n", bad->name, bad->errormsg);
	}
}

void	insert_bad(t_binarytree **bad_items, char *bad_name,
					char *error)
{
	if (!*bad_items)
	{
		*bad_items = ft_treenew(new_bad(bad_name, error));
	}
	else
	{
		if (ft_strcmp(bad_name, ((t_bad *)((*bad_items)->content))->name) >= 0)
		{
			insert_bad(&(*bad_items)->right, bad_name, error);
		}
		else
		{
			insert_bad(&(*bad_items)->left, bad_name, error);
		}
	}
}

void	delete_bad(t_bad *bad)
{
	if (bad)
	{
		ft_memdel((void **)&bad);
	}
}
