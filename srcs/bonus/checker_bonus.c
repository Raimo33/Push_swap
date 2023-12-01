/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:31:26 by craimond          #+#    #+#             */
/*   Updated: 2023/11/30 18:46:22 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static char	check_duplicates(int *sorted_arr, short size);
static void	check_sorting(t_list *stack_a);
static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a);
static void	make_moves(t_stacks stacks);

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	int			*sorted_arr;

	if (argc < 3)
	{
		f_atol(argv[1]);
		return (0);
	}
	sorted_arr = malloc(sizeof(int) * (argc - 1));
	stacks.sa = malloc(sizeof(t_list *));
	stacks.sb = malloc(sizeof(t_list *));
	*(stacks.sa) = 0;
	*(stacks.sb) = 0;
	if (!stacks.sa || !stacks.sb || !sorted_arr)
		free_everything(1, stacks, sorted_arr);
	init(argc, &sorted_arr, argv, stacks.sa);
	check_duplicates(sorted_arr, argc - 1);
	make_moves(stacks);
	check_sorting(*(stacks.sa));
	f_lstclear(stacks.sa);
	free_everything(0, stacks, sorted_arr);
}

static void	make_moves(t_stacks stacks)
{
	char *move;

	move = get_next_line(0);
	while (move)
	{
		if (f_strcmp(move, "ra\n") || f_strcmp(move, "rb\n"))
			rotate((t_list **)(((uintptr_t)(stacks.sa)) * (f_strcmp(move, "ra\n"))
					+ ((uintptr_t)(stacks.sb)) * (f_strcmp(move, "rb\n"))));
		else if (f_strcmp(move, "rr\n"))
			rotate(stacks.sa) + rotate(stacks.sb);
		else if (f_strcmp(move, "rra\n") || f_strcmp(move, "rrb\n"))
			rev_rotate((t_list **)(((uintptr_t)(stacks.sa)) * (f_strcmp(move, "rra\n"))
					+ ((uintptr_t)(stacks.sb)) * (f_strcmp(move, "rrb\n"))));
		else if (f_strcmp(move, "rrr\n"))
			rev_rotate(stacks.sa) + rev_rotate(stacks.sb);
		else if (f_strcmp(move, "sa\n") || f_strcmp(move, "sb\n"))
			swap((t_list **)(((uintptr_t)stacks.sa) * (f_strcmp(move, "sa\n"))
					+ ((uintptr_t)stacks.sb) * (f_strcmp(move, "sb\n"))));
		else if (f_strcmp(move, "ss\n"))
			swap(stacks.sa) + swap(stacks.sb);
		else
			error(2);
		free(move);
		move = get_next_line(0);
	}
}

static void	check_sorting(t_list *stack_a)
{
	while (stack_a->next)
	{
		if (stack_a->n > stack_a->next->n)
			write(1, "KO\n", 3);
		stack_a = stack_a->next;
	}
	if (!stack_a)
		write(1, "OK\n", 3);
}

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a)
{
	t_list	*new_node;
	int		i;

	i = 0;
	while (++i < argc)
		(*sorted_arr)[i - 1] = f_atol(argv[i]);
	while (--i > 0)
	{
		new_node = f_lstnew((*sorted_arr)[i - 1]);
		if (!new_node)
			error(1);
		ft_lstadd_front(stack_a, new_node);
	}
	quicksort((*sorted_arr), 0, argc - 2);
}

static char	check_duplicates(int *sorted_arr, short size)
{
	while (--size > 0)
		if (sorted_arr[size - 1] == sorted_arr[size])
			error(2);
	return (1);
}
