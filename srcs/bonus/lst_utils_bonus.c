/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 18:09:30 by craimond          #+#    #+#             */
/*   Updated: 2023/11/30 18:16:09 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

t_list	*f_lstnew(int n)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node->n = n;
	new_node->dist = 0;
	new_node->easiness = SHRT_MAX;
	new_node->next = NULL;
	return (new_node);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

void	f_lstclear(t_list **lst)
{
	if (!(*lst) || !lst)
		return ;
	if ((*lst)->next)
		f_lstclear(&(*lst)->next);
	free(*lst);
	*lst = NULL;
}
