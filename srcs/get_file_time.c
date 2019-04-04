/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_time.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:18:39 by abarnett          #+#    #+#             */
/*   Updated: 2019/04/04 15:21:11 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "file.h"
#include <sys/stat.h>

#ifdef __linux__

void	get_time(t_file *file, struct stat *stats)
{
	file->tv_sec = stats->st_mtim.tv_sec;
	file->tv_nsec = stats->st_mtim.tv_nsec;
}

#elif defined __APPLE__

void	get_time(t_file *file, struct stat *stats)
{
	file->tv_sec = stats->st_mtimespec.tv_sec;
	file->tv_nsec = stats->st_mtimespec.tv_nsec;
}

#else

void	get_time(t_file *file, struct stat *stats)
{
	file->tv_sec = 0;
	file->tv_nsec = 0;
}

#endif
