/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 14:16:52 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/01 14:21:28 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "files.h"
#include "libftprintf.h"

void	print_file(t_file *file)
{
	if (file)
	{
		ft_printf("%s\n", file->name);
	}
}

void	print_file_long(t_file *file)
{
	if (file)
	{
		ft_printf("%s %s\n", file->rights, file->name);
	}
}
