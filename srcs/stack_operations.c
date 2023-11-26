/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:14:39 by craimond          #+#    #+#             */
/*   Updated: 2023/11/26 12:16:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	rotate(t_list **stack, char ab, char **result)
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
	if (ab == 'a')
		**result = 1;
	else
		**result = 2;
	(*result)++;
}

void	rev_rotate(t_list **stack, char ab, char **result)
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
	if (ab == 'a')
		**result = 4;
	else
		**result = 5;
	(*result)++;
}

void	push(t_list **stack_from, t_list **stack_to, char ab, char **result)
{
	t_list	*tmp;

	if (stack_to && stack_from && *stack_from)
	{
        tmp = *stack_from;
        *stack_from = (*stack_from)->next;
        tmp->next = *stack_to;
        *stack_to = tmp; 
	}
	if (ab == 'a')
		**result = 7;
	else
		**result = 8;
	(*result)++;
}

void	swap(t_list **stack, char ab, char **result)
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
	if (ab == 'a')
		**result = 9;
	else
		**result = 10;
	(*result)++;
}
