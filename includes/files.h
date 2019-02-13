/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:21:14 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/13 12:52:16 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILES_H
# define FILES_H

# define T_FILE(t) ((t_file *)((t)->content))

typedef struct s_binarytree	t_binarytree;

typedef struct		s_file
{
	char			*name;
	char			*path;
	char			*rights;
	unsigned int	links;
	char			*user;
	char			*group;
	char			*date;
	unsigned long	bytes;
}					t_file;

void				get_file_info(t_file *file, char *path_to_file);
t_file				*new_file(char *filename, char *path_to_file, int info);
void				get_info(t_file *file, char *path);
void				insert_file(t_binarytree **files, t_file *insert,
						int (*compare)(char *s1, char *s2));
void				print_file(t_file *file);
void				print_file_long(t_file *file);
void				delete_file(t_file *file);

#endif
