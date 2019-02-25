/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:40:42 by alan              #+#    #+#             */
/*   Updated: 2019/02/24 18:35:35 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "files.h"
#include "libftprintf.h"

/*
** This file contains the default color macros, and filetype extensions used
** for color matching.
*/

#include "config.h"

static char		*check_rights(char *rights)
{
	if (rights)
	{
		if (*rights == 'd')
			return (COLOR_DIR);
		if (*rights == 'l')
			return (COLOR_LINK);
		if (rights[3] == 'x' || rights[6] == 'x' || rights[9] == 'x')
			return (COLOR_EXE);
	}
	return (0);
}

static int		check_extension_list(char *filename,
					const char **extensions_list)
{
	int	filename_len;
	int	i;
	int	ext_len;

	filename_len = ft_strlen(filename);
	i = 0;
	while (extensions_list[i])
	{
		ext_len = ft_strlen(extensions_list[i]);
		if (ft_strequ(filename + filename_len - ext_len, extensions_list[i]))
			return (1);
		++i;
	}
	return (0);
}

static char 	*check_extension(char *filename)
{
	if (check_extension_list(filename, zip_extensions))
	{
		return (COLOR_ZIP);
	}
	if (check_extension_list(filename, picture_extensions))
	{
		return (COLOR_PICTURE);
	}
	if (check_extension_list(filename, video_extensions))
	{
		return (COLOR_VIDEO);
	}
	if (check_extension_list(filename, audio_extensions))
	{
		return (COLOR_AUDIO);
	}
	return (0);
}

char			*get_color(t_file *file)
{
	char	*color;

	color = check_rights(file->rights);
	if (color)
		return (color);
	color = check_extension(file->name);
	if (color)
		return (color);
	return ("");
}
