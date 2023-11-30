/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 15:17:47 by craimond          #+#    #+#             */
/*   Updated: 2023/11/30 12:44:49 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	show_moves(short move_counts[], char *moves[]);
static void	init(char *moves[], short move_counts[]);

void	merge_moves(char **result)
{
	char	*moves[10];
	short	move_counts[5];
	char	*start;
	char	*end;

	init(moves, move_counts);
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
}

static void	show_moves(short move_counts[], char *moves[])
{
	int	i;

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

static void	init(char *moves[], short move_counts[])
{
	unsigned char	i;

	moves[0] = "ra\n";
	moves[1] = "rb\n";
	moves[2] = "rr\n";
	moves[3] = "rra\n";
	moves[4] = "rrb\n";
	moves[5] = "rrr\n";
	moves[6] = "pa\n";
	moves[7] = "pb\n";
	moves[8] = "sa\n";
	moves[9] = "sb\n";
	i = 0;
	while (i < 5)
		move_counts[(int)i++] = 0;
}
