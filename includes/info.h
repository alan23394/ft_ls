/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 22:46:27 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/21 20:50:21 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# define SIX_MONTHS_SECONDS (15724800)

# ifdef __linux__
#  define MAJ(num) (((num) & 0xFF00) >> 8)
#  define MIN(num) ((num) & 0xFF)
# elif defined __APPLE__
#  define MAJ(num) (((num) & 0xFF000000) >> 24)
#  define MIN(num) ((num) & 0x00FFFFFF)
# endif

typedef struct	s_file t_file;

int				get_file_info(t_file *file, int options, int link);

#endif
