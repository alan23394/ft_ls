/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/01 15:17:01 by abarnett          #+#    #+#             */
/*   Updated: 2019/03/23 07:31:11 by alan             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include "ft_string.h"
#include "ft_printf.h"

/*
** The value of this variable describes what color to use for which attribute
** when colors are enabled with CLICOLOR. This string is a concatenation of
** pairs of the format fb, where f is the foreground color and b is the
** background color.
**
** 		The color designators are as follows:
**
** 			a	black
** 			b	red
** 			c	green
** 			d	brown
** 			e	blue
** 			f	magenta
** 			g	cyan
** 			h	light grey
** 			A	bold black, usually shows up as dark grey
** 			B	bold red
** 			C	bold green
** 			D	bold brown, usually shows up as yellow
** 			E	bold blue
** 			F	bold magenta
** 			G	bold cyan
** 			H	bold light grey; looks like bright white
** 			x	default foreground or background
**
** 		Note that the above are standard ANSI colors. The actual
** 		display may differ depending on the color capabilities of the
** 		terminal in use.
**
** 		The order of the attributes are as follows:
**
** 			1.	directory
** 			2.	symbolic link
** 			3.	socket
** 			4.	pipe
** 			5.	executable
** 			6.	block special
** 			7.	character special
** 			8.	executable with setuid bit set
** 			9.	executable with setgid bit set
** 			10.	directory writable to others, with sticky bit
** 			11.	directory writable to others, without sticky bit
**
** 		The default is "exfxcxdxbxegedabagacad", i.e. blue foreground
** 		and default background for regular directories, black
** 		foreground and red background for setuid executables, etc.
*/
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
