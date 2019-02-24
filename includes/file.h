/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:21:14 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/21 22:50:27 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILE_H
# define FILE_H

# define T_FILE(t) ((t_file *)((t)->content))

typedef struct 		s_binarytree t_binarytree;

typedef struct		s_file
{
	char			*name;
	unsigned long	tv_sec;
	unsigned long	tv_nsec;
	char			*path;
	char			*rights;
	unsigned int	links;
	char			*user;
	char			*group;
	char			*date;
	unsigned long	bytes;
	unsigned long	blocks;
}					t_file;

t_file				*new_file(char *filename, char *path_to_file);
void				insert_file(t_binarytree **files, t_file *insert,
						int (*compare)());
void				delete_file(t_file *file);

#endif
