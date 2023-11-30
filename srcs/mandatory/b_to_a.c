/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_to_a.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:22:03 by craimond          #+#    #+#             */
/*   Updated: 2023/11/30 13:10:53 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static t_list	*get_brother(t_list *stack, int n);

void	push_easiest(t_stacks stacks, char **result)
{
	t_list	*tmp_from;
	t_list	*easiest;

	reset_distances(*(stacks.sb));
	tmp_from = *(stacks.sb);
	easiest = NULL;
	while (tmp_from)
	{
		tmp_from->brother = get_brother(*(stacks.sa), tmp_from->n);
		tmp_from->easiness = abs(tmp_from->dist) + abs(tmp_from->brother->dist);
		if (!easiest || tmp_from->easiness < easiest->easiness)
			easiest = tmp_from;
		if (easiest->easiness <= 1)
			break ;
		tmp_from = tmp_from->next;
	}
	move_to_top(stacks.sb, easiest, 'b', result);
	move_to_top(stacks.sa, easiest->brother, 'a', result);
	push(stacks.sb, stacks.sa, 'a', result);
	reset_distances(*(stacks.sa));
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
