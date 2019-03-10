/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 16:09:10 by alan              #+#    #+#             */
/*   Updated: 2019/03/09 16:11:49 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ARGS_H
# define ARGS_H

typedef struct		s_args
{
	t_binarytree	*files;
	t_binarytree	*dirs;
	t_binarytree	*bad;
}					t_args;

void				process_arg(char *param, t_args *trees, t_flags *flags,
						t_dir *files_dir);

#endif
