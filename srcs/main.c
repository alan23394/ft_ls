/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:25:08 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/07 19:11:08 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"
#include <dirent.h>

/*
** Allowed functions from dirent.h:
** opendir
** readdir
** closdir
*/

void	list_folder(char *str)
{
	DIR				*directory;
	struct dirent	*dir_ent;

	directory = opendir(str);
	dir_ent = readdir(directory);
	closedir(directory);
}

int		main(int argc, char **argv)
{
	(void)argv;
	if (argc == 1)
		list_folder(".");
	return (0);
}
