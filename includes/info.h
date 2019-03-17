/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 22:46:27 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/16 22:37:48 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# define SIX_MONTHS_SECONDS (15778476)

typedef struct	s_file t_file;

int				get_file_info(t_file *file, int options, int link);

#endif
