/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 22:34:54 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/03 20:05:30 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRINTING_H
# define PRINTING_H

typedef struct 		s_dir t_dir;
typedef struct		s_file t_file;
typedef struct		s_binarytree t_binarytree;
typedef struct		s_flags t_flags;

void				print_dir(t_dir *dir, t_binarytree *files, t_flags *flags);
void				print_file(t_file *file);
void				print_file_color(t_file *file);
void				print_file_long(t_file *file, t_dir *dir);
void				print_file_long_color(t_file *file, t_dir *dir);

#endif
