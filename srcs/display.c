/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:17:47 by craimond          #+#    #+#             */
/*   Updated: 2023/11/26 15:53:00 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	show_moves(int move_counts[], char *moves[]);

void	merge_moves(char **result)
{
	char	*start;
	char	*end;
	int		move_counts[5] = {0, 0, 0, 0, 0}; //ra, rb, NULL, rra, rrb
	char	*moves[10] = {"ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n", "pa\n", "pb\n", "sa\n", "sb\n"};

	while (*(*result - 1) != 0)
		(*result)--;
	start = *result;
	end = *result;
	while (*end != 0)
	{
		while (*end < 6 && *end != 0)
			end++;
		while (start != end)
			move_counts[*start++ - 1] += 1;
		show_moves(move_counts, moves);
		if (*end != 0)
			ft_putstr(moves[*end - 1]);
		start = ++end;
	}
	free(*result - 1);
}

static void	show_moves(int move_counts[], char *moves[])
{
	int i;

	i = 0;
	while (i < 5)
	{
		while (move_counts[i] > 0 && move_counts[i + 1] > 0)
		{
			ft_putstr(moves[i + 2]);
			move_counts[i]--;
			move_counts[i + 1]--;
		}
		while (move_counts[i] > 0)
		{
			ft_putstr(moves[i]);
			move_counts[i]--;
		}
		while (move_counts[i + 1] > 0)
		{
			ft_putstr(moves[i + 1]);
			move_counts[i + 1]--;
		}
		i += 3;
	}
}
