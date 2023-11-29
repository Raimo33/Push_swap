/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:14:39 by craimond          #+#    #+#             */
/*   Updated: 2023/11/29 12:15:32 by craimond         ###   ########.fr       */
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
    	*(*result)++ = 1 * (ab == 'a') + 2 * (ab == 'b');
	}
    else
        swap(stack, ab, result);
}

void rev_rotate(t_list **stack, char ab, char **result)
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
        *(*result)++ = 4 * (ab == 'a') + 5 * (ab == 'b');
	}
    else
        swap(stack, ab, result);
}

void push(t_list **stack_from, t_list **stack_to, char ab, char **result)
{
	t_list	*tmp;

	if (stack_to && stack_from && *stack_from)
	{
        tmp = *stack_from;
        *stack_from = (*stack_from)->next;
        tmp->next = *stack_to;
        *stack_to = tmp;
        *(*result)++ = 7 * (ab == 'a') + 8 * (ab == 'b');
	}
}


void swap(t_list **stack, char ab, char **result)
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
        *(*result)++ = 9 * (ab == 'a') + 10 * (ab == 'b');
	}
}

void	move_to_top(t_list **stack, t_list *node, char ab, char **result)
{
	if (node->dist > 0)
		while (*stack != node)
			 rotate(stack, ab, result);
	else
		while (*stack != node)
			rev_rotate(stack, ab, result);
    reset_distances(*stack);
}
