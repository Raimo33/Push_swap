/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:13:32 by craimond          #+#    #+#             */
/*   Updated: 2023/11/27 14:24:18 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

t_list	*f_lstnew(int n)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
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

int	f_lstclear(t_list **lst)
{
	if (*lst == NULL || lst == NULL)
		return (0);
	if ((*lst)->next != NULL)
		f_lstclear(&(*lst)->next);
	free(*lst);
	*lst = NULL;
	return (0);
}

short	lst_len(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

short	get_distance(t_list *stack, t_list *node)
{
	int dist;
	int	len;

	len = lst_len(stack);
	dist = 0;
	while (stack != node && ++dist)
		stack = stack->next;
	if (dist > len / 2)
		return ((len - dist) * -1);
	return(dist);
}
