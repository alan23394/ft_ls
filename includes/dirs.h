/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:53:28 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/31 12:55:11 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRS_H
# define DIRS_H

# define T_DIR(t) ((t_dir *)((t)->content))

typedef struct s_binarytree	t_binarytree;

typedef struct		s_dir
{
	char			*name;
	unsigned int	user_maxlen;
	unsigned int	group_maxlen;
	unsigned int	links_maxlen;
	unsigned int	bytes_maxlen;
	unsigned int	total_size;
}					t_dir;

t_dir				*new_dir(char *item);
void				insert_dir(t_binarytree **dirs, char *insert,
						int (*compare)(char *s1, char *s2));
void				delete_dir(t_dir *dir);

#endif
