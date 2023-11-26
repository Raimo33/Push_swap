/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:21:54 by craimond          #+#    #+#             */
/*   Updated: 2023/11/26 18:04:09 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	divide_into_chunks(t_list **stack_a, t_list **stack_b, int *sorted_arr, short n_chunks, char **result)
{
	t_list	*node;
	int		i;
	int		j;
	int		key_nbr;
	int		key_nbr2;
	int		arr_len;

	j = 1;
	arr_len = lst_len(*stack_a);
	node = *stack_a;
	while (j <= n_chunks - 1)
	{
		key_nbr = sorted_arr[(arr_len / n_chunks) * j - 1];
		key_nbr2 = sorted_arr[(arr_len / n_chunks) * (j + 1) - 1];
		if (j == n_chunks - 1)
			key_nbr2 = sorted_arr[arr_len - 2];
		i = -1;
		while (++i < (arr_len / n_chunks * 2))
		{
			while (node && node->n > key_nbr2)
				node = node->next;
			move_to_top(stack_a, node, 'a', result);
			push(stack_a, stack_b, 'b', result);
			if (node->n <= key_nbr)
				rotate(stack_b, 'b', result);
			node = *stack_a;
		}
		j += 2;
	}
	while((*stack_a)->next->next->next)
	{
		if ((*stack_a)->n >= sorted_arr[arr_len - 1])
			rotate(stack_a, 'a', result);
		push(stack_a, stack_b, 'b', result);
	}
}

void	handle_three(t_list **stack, char ab, char **result)
{
	if (FIRST(*stack) > SECOND(*stack) && SECOND(*stack) < THIRD(*stack) && FIRST(*stack) < THIRD(*stack)) //[2,1,3]
		swap(stack, ab, result);
	else if (FIRST(*stack) > SECOND(*stack) && SECOND(*stack) > THIRD(*stack)) //[3,2,1]
	{
		swap(stack, ab, result);
		rev_rotate(stack, ab, result);
	}
	else if (FIRST(*stack) > SECOND(*stack) && SECOND(*stack) < THIRD(*stack)) //[3,1,2]
		rotate(stack, ab, result);
	else if (FIRST(*stack) < SECOND(*stack) && SECOND(*stack) > THIRD(*stack) && FIRST(*stack) < THIRD(*stack)) //[1,3,2]
	{
		swap(stack, ab, result);
		rotate(stack, ab, result);
	}
	else if (FIRST(*stack) < SECOND(*stack) && SECOND(*stack) > THIRD(*stack)) //[2,3,1]
		rev_rotate(stack, ab, result);
}

