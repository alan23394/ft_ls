/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/24 16:52:34 by alan              #+#    #+#             */
/*   Updated: 2019/04/04 15:36:04 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# define COLOR_DIR "\e[1;34m"
# define COLOR_EXE "\e[1;32m"
# define COLOR_LINK "\e[1;36m"
# define COLOR_ZIP "\e[0;35m"
# define COLOR_PICTURE "\e[0;32m"
# define COLOR_AUDIO "\e[0;36m"
# define COLOR_VIDEO "\e[0;33m"
# define COLOR_NORM "\e[m"

static const char	*g_zip_extensions[] = {
	".zip",
	".rar",
	".7z",
	".tar",
	".gz",
	".tar.gz",
	0
};

static const char	*g_picture_extensions[] = {
	".png",
	".jpg",
	".jpeg",
	".bmp",
	".gif",
	0
};

static const char	*g_video_extensions[] = {
	".webm",
	".mp4",
	0
};

static const char	*g_audio_extensions[] = {
	".mp3",
	".wav",
	".flac",
	0
};

#endif
