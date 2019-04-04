/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 18:23:26 by abarnett          #+#    #+#             */
/*   Updated: 2019/04/04 15:52:02 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

typedef struct s_file		t_file;
typedef struct s_dir		t_dir;
typedef struct s_flags		t_flags;
typedef struct s_binarytree	t_binarytree;

char			*get_dirname(char *cur, char *add);
void			update_dir(t_dir *dir, t_file *file);
t_binarytree	*load_tree(t_binarytree *dirtree, t_flags *flags, char **error);
void			recurse_dirs(t_binarytree *dirs, t_flags *flags);
t_binarytree	*get_dirs(char **folders, t_flags *flags);

#endif
