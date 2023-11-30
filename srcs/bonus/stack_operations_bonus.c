/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:58:01 by craimond          #+#    #+#             */
/*   Updated: 2023/11/30 17:43:10 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

char	rotate(t_list **stack)
{
	t_list	*first;
	t_list	*tmp;

	if (stack && *stack && (*stack)->next)
	{
		first = *stack;
		*stack = first->next;
		tmp = *stack;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = first;
		first->next = NULL;
	}
	return (0);
}

char	rev_rotate(t_list **stack)
{
	t_list	*last;
	t_list	*tmp;

	if (stack && *stack && (*stack)->next)
	{
		tmp = *stack;
		while (tmp->next->next)
			tmp = tmp->next;
		last = tmp->next;
		last->next = *stack;
		tmp->next = NULL;
		*stack = last;
	}
	return (0);
}

char	push(t_list **stack_from, t_list **stack_to)
{
	t_list	*tmp;

	if (stack_to && stack_from && *stack_from)
	{
		tmp = *stack_from;
		*stack_from = (*stack_from)->next;
		tmp->next = *stack_to;
		*stack_to = tmp;
	}
	return (0);
}

char	swap(t_list **stack)
{
	t_list	*first;
	t_list	*second;

	if (stack && *stack && (*stack)->next)
	{
		first = *stack;
		second = first->next;
		first->next = second->next;
		second->next = first;
		*stack = second;
	}
	return (0);
}