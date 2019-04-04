/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 22:46:27 by abarnett          #+#    #+#             */
/*   Updated: 2019/04/04 11:15:56 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# define SIX_MONTHS_SECONDS (15724800)
# define MAJ(num) (((num) & 0xFF000000) >> 24)
# define MIN(num) ((num) & 0x00FFFFFF)

typedef struct s_file	t_file;

char	get_extended_attributes(char *filename);
int		get_file_info(t_file *file, int options, int link);

#endif
