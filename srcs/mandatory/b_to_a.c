/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:22:03 by craimond          #+#    #+#             */
/*   Updated: 2023/12/02 15:20:23 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_list	*get_brother(t_list *stack, int n);

void	push_cheapest(t_stacks stacks, int max, char **result)
{
	t_list	*tmp_from;
	t_list	*cheapest;

	reset_distances(*stacks.sb);
	tmp_from = *stacks.sb;
	cheapest = NULL;
	while (tmp_from)
	{
		tmp_from->brother = get_brother(*stacks.sa, tmp_from->n);
		tmp_from->cost = abs(tmp_from->dist) + abs(tmp_from->brother->dist) + (max - tmp_from->n);
		if (!cheapest || tmp_from->cost < cheapest->cost)
			cheapest = tmp_from;
		if (cheapest->cost <= 1)
			break ;
		tmp_from = tmp_from->next;
	}
	move_to_top(stacks.sb, cheapest, 'b', result);
	move_to_top(stacks.sa, cheapest->brother, 'a', result);
	push(stacks.sb, stacks.sa, 'a', result);
	reset_distances(*stacks.sa);
}

void	adjust(t_list **stack_a, int *sorted_arr, char **result)
{
	t_list	*min;

	min = *stack_a;
	while (min && min->n != sorted_arr[0])
		min = min->next;
	move_to_top(stack_a, min, 'a', result);
}

static t_list	*get_brother(t_list *stack, int n)
{
	t_list	*brother;
	t_list	*tmp;
	long	diff;
	long	nl;

	nl = n;
	brother = NULL;
	tmp = stack;
	while (tmp)
	{
		diff = nl - tmp->n;
		if (diff < 0 && (!brother || diff > nl - brother->n))
			brother = tmp;
		tmp = tmp->next;
		if (tmp == stack)
			break ;
	}
	return (brother);
}
