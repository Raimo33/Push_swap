/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:22:03 by craimond          #+#    #+#             */
/*   Updated: 2023/11/26 18:14:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_list	*get_easiest(t_list *stack_from);
static t_list	*get_closest(t_list *stack, int n);

void	push_easiest(t_list **stack_from, t_list **stack_to, int key_nbr, char **result)
{
	t_list	*tmp_from;
	t_list	*closest_to;
	t_list	*easiest;

	tmp_from = *stack_from;
	while (tmp_from)
	{
		closest_to = get_closest(*stack_to, tmp_from->n);
		//////////O(n^3) perche' get distance cicla la lista, while(tmp_from) cicla la lista, e push_easiest e' ciclato nella lista
		tmp_from->easiness = ABS(get_distance(*stack_to, closest_to)) + ABS((get_distance(*stack_from, tmp_from)));
		if (tmp_from->n < key_nbr)
			tmp_from->easiness = SHRT_MAX;
		tmp_from = tmp_from->next;
	}
	easiest = get_easiest(*stack_from);
	move_to_top(stack_to, get_closest(*stack_to, easiest->n), 'a', result);
	move_to_top(stack_from, easiest, 'b', result);
	push(stack_from, stack_to, 'a', result);
}

void	adjust(t_list **stack_a, int *sorted_arr, char **result)
{
	t_list	*min;

	min = *stack_a;
	while (min && min->n != sorted_arr[0])
		min = min->next;
	move_to_top(stack_a, min, 'a', result);
}

static t_list	*get_easiest(t_list *stack_from)
{
	t_list	*easiest;

	easiest = stack_from;
	while (stack_from && easiest->easiness > 1)
	{
		if (stack_from->easiness < easiest->easiness)
			easiest = stack_from;
		stack_from = stack_from->next;
	}
	return (easiest);
}

static t_list	*get_closest(t_list *stack, int n)
{
	t_list	*closest;
	int		best_n;

	best_n = INT_MAX;
	closest = NULL;
	while (stack)
	{
		if (n - stack->n < 0 && n - stack->n > n - best_n)
		{
			best_n = stack->n;
			closest = stack;
		}
		stack = stack->next;
	}
	return (closest);
}
