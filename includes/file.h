/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:21:14 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/09 01:25:02 by alan             ###   ########.fr       */
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
	char			*color;
}					t_file;

t_file				*new_file(char *path_to_file);
t_file				*new_file_full_name(char *path_to_file);
void				delete_file(t_file *file);
char				*get_name_from_path(char *path);
void				insert_file(t_binarytree **files, t_file *insert,
						int (*compare)());

#endif
