/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_binarytree.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarnett <alanbarnett328@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/22 00:28:11 by abarnett          #+#    #+#             */
/*   Updated: 2019/01/29 13:33:45 by abarnett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_BINARYTREE_H
# define FT_BINARYTREE_H

# include "libft.h"

typedef struct			s_binarytree
{
	void				*content;
	struct s_binarytree	*left;
	struct s_binarytree	*right;
}						t_binarytree;

t_binarytree			*ft_treenew(void *item);
void					ft_treeinsert(t_binarytree **tree, void *insert,
							int (*compare)());
void					ft_treeiter_ltor(t_binarytree *tree, void (*f)());
void					ft_treeiter_rtol(t_binarytree *tree, void (*f)());
void					ft_treedel(t_binarytree **tree,
							void (*del)());

#endif
