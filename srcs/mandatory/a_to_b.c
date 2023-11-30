/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a_to_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 12:21:54 by craimond          #+#    #+#             */
/*   Updated: 2023/11/30 13:18:07 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	push_two_chunks(t_stacks stacks, struct s_keynbrs keynbrs,
				unsigned short size, char **result);

char	is_sorted(t_list *stack, int *sorted_arr)
{
	t_list	*tmp;
	short	i;
	short	arr_len;

	i = -1;
	arr_len = lst_len(stack);
	tmp = stack;
	while (tmp && tmp->n == sorted_arr[++i])
		tmp = tmp->next;
	if (!tmp)
		return (1);
	while (sorted_arr[i] != tmp->n)
		i++;
	while (sorted_arr[++i - 1] == tmp->n)
	{
		if (i >= arr_len)
			i = 0;
		tmp = tmp->next;
		if (!tmp)
			return (-1);
	}
	return (0);
}

void	divide_into_chunks(t_stacks stacks, int *sorted_arr, char **result,
unsigned short size)
{
	struct s_keynbrs	keynbrs;
	unsigned char		j;
	unsigned char		n_chunks;

	j = 1;
	n_chunks = get_n_chunks(size);
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
	while ((*(stacks.sa))->next->next->next)
	{
		if ((*(stacks.sa))->n >= sorted_arr[size - 1])
			rotate(stacks.sa, 'a', result);
		push(stacks.sa, stacks.sb, 'b', result);
	}
}

static void	push_two_chunks(t_stacks stacks, struct s_keynbrs keynbrs,
unsigned short size, char **result)
{
	short			i;
	unsigned char	n_chunks;
	t_list			*node;

	node = *(stacks.sa);
	n_chunks = get_n_chunks(size);
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
	int	first;
	int	second;
	int	third;

	first = (*stack)->n;
	second = (*stack)->next->n;
	third = (*stack)->next->next->n;
	if (first > second && second < third && first < third)
		swap(stack, ab, result);
	else if (first > second && second > third)
	{
		swap(stack, ab, result);
		rev_rotate(stack, ab, result);
	}
	else if (first > second && second < third)
		rotate(stack, ab, result);
	else if (first < second && second > third && first < third)
	{
		swap(stack, ab, result);
		rotate(stack, ab, result);
	}
	else if (first < second && second > third)
		rev_rotate(stack, ab, result);
}
