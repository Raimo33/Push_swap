/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:13:32 by craimond          #+#    #+#             */
/*   Updated: 2023/11/30 18:16:00 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

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

short	lst_len(t_list *lst)
{
	int		len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

void	reset_distances(t_list *stack)
{
	short	size;
	short	i;

	i = 0;
	size = lst_len(stack);
	while (stack && i < size / 2)
	{
		stack->dist = i++;
		stack = stack->next;
	}
	while (stack && i > 0)
	{
		stack->dist = -(i--);
		stack = stack->next;
	}
}
