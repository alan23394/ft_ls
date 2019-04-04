/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file_usergroup.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 15:01:18 by abarnett          #+#    #+#             */
/*   Updated: 2019/04/04 15:09:35 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_utils.h"
#include "ft_string.h"
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>

char	*get_file_user(struct stat *stats)
{
	struct passwd	*id;
	char			*username;

	id = getpwuid(stats->st_uid);
	if (id)
	{
		username = ft_strdup(id->pw_name);
	}
	else
	{
		username = ft_itoa(stats->st_uid);
	}
	return (username);
}

char	*get_file_group(struct stat *stats)
{
	struct group	*id;
	char			*groupname;

	id = getgrgid(stats->st_gid);
	if (id)
	{
		groupname = ft_strdup(id->gr_name);
	}
	else
	{
		groupname = ft_itoa(stats->st_gid);
	}
	return (groupname);
}
