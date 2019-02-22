/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dirs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/29 11:53:28 by abarnett          #+#    #+#             */
/*   Updated: 2019/02/21 17:39:13 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DIRS_H
# define DIRS_H

# define T_DIR(t) ((t_dir *)((t)->content))

typedef struct s_binarytree	t_binarytree;
typedef struct s_flags		t_flags;

typedef struct		s_dir
{
	char			*name;
	char			*path;
	unsigned long	tv_sec;
	unsigned long	tv_nsec;
	unsigned int	links_maxlen;
	unsigned int	user_maxlen;
	unsigned int	group_maxlen;
	unsigned int	bytes_maxlen;
	unsigned long	total_size;
}					t_dir;

t_dir				*new_dir(char *new_dirname);
void				insert_dir(t_binarytree **dirs, char *new_dirname,
						int (*compare)(char *s1, char *s2));
void				print_dir(t_dir *dir, t_binarytree *files, t_flags *flags);
void				delete_dir(t_dir *dir);

#endif
