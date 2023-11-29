/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:21:54 by craimond          #+#    #+#             */
/*   Updated: 2023/11/29 15:22:43 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

typedef struct s_keynbrs
{
	int	n1;
	int	n2;
}				t_keynbrs;

static void	push_two_chunks(t_stacks stacks, t_keynbrs keynbrs, unsigned short size, char **result);

void	divide_into_chunks(t_stacks stacks, int *sorted_arr, char **result, unsigned short size)
{
	t_list				*node;
	t_keynbrs			keynbrs;
	unsigned char		j;
	unsigned char		n_chunks;

	j = 1;
	n_chunks = N_CHUNKS(size);
    reset_distances(*(stacks.sa));
	while (j <= n_chunks - 1)
	{
		keynbrs.n1 = sorted_arr[(size / n_chunks) * j - 1];
		if (j == n_chunks - 1)
			keynbrs.n2 = sorted_arr[size - 2];
		else
			keynbrs.n2 = sorted_arr[(size / n_chunks) * (j + 1) - 1];
		push_two_chunks(stacks, keynbrs, size, result);
		j += 2;
	}
	while((*(stacks.sa))->next->next->next)
	{
		if ((*(stacks.sa))->n >= sorted_arr[size - 1])
			rotate(stacks.sa, 'a', result);
		push(stacks.sa, stacks.sb, 'b', result);
	}
}

static void	push_two_chunks(t_stacks stacks, t_keynbrs keynbrs, unsigned short size, char **result)
{
	short			i;
	unsigned char	n_chunks;
	t_list			*node;

	node = *(stacks.sa);
	n_chunks = N_CHUNKS(size);
	i = -1;
	while (++i < ((size / n_chunks) * 2) && (*(stacks.sa))->next->next->next)
	{
		while (node && node->n > keynbrs.n2)
			node = node->next;
		move_to_top(stacks.sa, node, 'a', result);
		push(stacks.sa, stacks.sb, 'b', result);
		if (node->n <= keynbrs.n1)
			rotate(stacks.sb, 'b', result);
		node = *(stacks.sa);
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

