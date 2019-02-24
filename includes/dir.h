/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:53:28 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/21 22:45:05 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIR_H
# define DIR_H

# define T_DIR(t) ((t_dir *)((t)->content))

typedef struct s_binarytree	t_binarytree;

typedef struct		s_dir
{
	char			*name;
	unsigned long	tv_sec;
	unsigned long	tv_nsec;
	unsigned int	links_maxlen;
	unsigned int	user_maxlen;
	unsigned int	group_maxlen;
	unsigned int	bytes_maxlen;
	unsigned long	total_size;
}					t_dir;

t_dir				*new_dir(char *new_dirname);
void				insert_dir(t_binarytree **dirs, t_dir *new_dir,
						int (*compare)());
void				delete_dir(t_dir *dir);

#endif
