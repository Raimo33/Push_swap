/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:22:03 by craimond          #+#    #+#             */
/*   Updated: 2023/11/27 16:41:56 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void		reset_distances(t_list *stack);
static t_list	*get_closest(t_list *stack, int n);

void	push_easiest(t_list **stack_from, t_list **stack_to, int key_nbr, char **result)
{
	t_list	*tmp_from;
	t_list	*closest_to;
	t_list	*easiest;

	tmp_from = *stack_from;
	easiest = NULL;
	while (tmp_from)
	{
		closest_to = get_closest(*stack_to, tmp_from->n);
		tmp_from->easiness = tmp_from->dist + closest_to->dist;
		if (tmp_from->n >= key_nbr && (!easiest || tmp_from->easiness < easiest->easiness))
			easiest = tmp_from;
		if (easiest && easiest->easiness <= 1)
			break ; 
		tmp_from = tmp_from->next;
	}
	if (!easiest)
		return ;
	move_to_top(stack_to, get_closest(*stack_to, easiest->n), 'a', result);
	move_to_top(stack_from, easiest, 'b', result);
	push(stack_from, stack_to, 'a', result);
	reset_distances(*stack_from);
	reset_distances(*stack_to);
}

void	adjust(t_list **stack_a, int *sorted_arr, char **result)
{
	t_list	*min;

	min = *stack_a;
	while (min && min->n != sorted_arr[0])
		min = min->next;
	move_to_top(stack_a, min, 'a', result);
}

static void	reset_distances(t_list *stack)
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
		stack->dist = i--;
		stack = stack->next;
	}
}

static t_list	*get_closest(t_list *stack, int n)
{
	t_list	*closest;

	closest = NULL;
	while (stack)
	{
		if (n - stack->n < 0 && (!closest || n - stack->n > n - closest->n))
			closest = stack;
		stack = stack->next;
	}
	return (closest);
}
