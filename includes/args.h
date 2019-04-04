/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 16:09:10 by alan              #+#    #+#             */
/*   Updated: 2019/03/27 19:53:32 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

typedef struct		s_binarytree t_binarytree;

typedef struct		s_args
{
	t_binarytree	*files;
	t_binarytree	*dirs;
	t_binarytree	*bad;
}					t_args;

typedef struct		s_flags t_flags;
typedef struct		s_dir t_dir;

void				process_arg(char *param, t_args *trees, t_flags *flags,
						t_dir *files_dir);

#endif
