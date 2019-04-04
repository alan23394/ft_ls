/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_extended_attributes.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alan <alanbarnett328@gmail.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/04 10:28:15 by alan              #+#    #+#             */
/*   Updated: 2019/04/04 14:47:16 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_mem.h"
#include "ft_string.h"
#include <stdint.h>
#include <sys/xattr.h>
#include <sys/acl.h>

#define ACL_FLAG (0x1)
#define EXTENDED_FLAG (0x2)

static char	get_symbol_char(int type_bits)
{
	char	symbol;

	if (type_bits == ACL_FLAG)
		symbol = '+';
	else if (type_bits == EXTENDED_FLAG)
		symbol = '@';
	else if (type_bits == (ACL_FLAG | EXTENDED_FLAG))
		symbol = '*';
	else
		symbol = ' ';
	return (symbol);
}

#ifdef __APPLE__

/*
** Extended attributes
** acl_get_link_np
**	non-portable, sets up the access control list
**	if this works, return a +
** listxattr
** 	if this works, return a @
*/

char		get_extended_attributes(char *filename)
{
	acl_t	acl;
	ssize_t	xattr;
	uint8_t	type_bits;
	char	symbol;

	type_bits = 0;
	acl = acl_get_link_np(filename, ACL_TYPE_EXTENDED);
	if (acl)
		type_bits |= ACL_FLAG;
	xattr = listxattr(filename, 0, 0, XATTR_NOFOLLOW);
	if (xattr)
		type_bits |= EXTENDED_FLAG;
	symbol = get_symbol_char(type_bits);
	acl_free(acl);
	return (symbol);
}

#elif defined __linux__

/*
** This function takes xattrs, which is a list returned by listxattr, and len,
** which is the size it returns of how long the string is. Since it comes as
** multiple null-delimited strings in a row, I need the full length so I can
** figure out of there's more strings. I use the variable single_len to check
** the length of one string, which just grabs up until the null terminator.
**
** I set a flag in the type_bits variable with whether it's an extended
** attribute, or an access control list, that way I can check if it has one,
** the other, or both (not in normal ls) to determine the character.
**
** There's also the chance len comes in as 0, so I need to give an else case
** with just a single space.
*/

static char	check_acl_extended(char *xattrs, int len)
{
	int			single_len;
	u_int8_t	type_bits;
	char		symbol;

	type_bits = 0;
	while (len)
	{
		single_len = ft_strlen(xattrs);
		if (ft_strnstr(xattrs, "system.posix_acl", 16))
			type_bits |= ACL_FLAG;
		else
			type_bits |= EXTENDED_FLAG;
		xattrs += (single_len + 1);
		len -= (single_len + 1);
	}
	symbol = get_symbol_char(type_bits);
	return (symbol);
}

char		get_extended_attributes(char *filename)
{
	ssize_t		xattr_len;
	char		*xattrs;
	char		symbol;

	xattr_len = listxattr(filename, 0, 0);
	if (xattr_len > 0)
	{
		xattrs = (char *)ft_memalloc(sizeof(char) * xattr_len);
		xattr_len = listxattr(filename, xattrs, xattr_len);
		if (xattr_len > 0)
			symbol = check_acl_extended(xattrs, xattr_len);
		else
			symbol = ' ';
		ft_strdel(&xattrs);
	}
	else
	{
		symbol = ' ';
	}
	return (symbol);
}

#else

char		get_extended_attributes(char *filename)
{
	return (' ');
}

#endif
