/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:27 by craimond          #+#    #+#             */
/*   Updated: 2023/12/03 17:21:13 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a);
static char	check_duplicates(int *sorted_arr, short size);
static void	free_everything(char id, t_stacks stacks, int *sorted_arr,
				char *result);
static void	handle_cases(t_stacks stacks, int *sorted_arr, char **result,
				unsigned short size);

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	int			*sorted_arr;
	char		*result;

	if (argc < 3)
	{
		if (argv[1])
			f_atol(argv[1]);
		return (0);
	}
	result = ft_calloc(N_MOVES, sizeof(char));
	sorted_arr = malloc(sizeof(int) * (argc - 1));
	stacks.sa = malloc(sizeof(t_list *));
	stacks.sb = malloc(sizeof(t_list *));
	*stacks.sa = 0;
	*stacks.sb = 0;
	if (!result++ || !stacks.sa || !stacks.sb || !sorted_arr)
		free_everything(1, stacks, sorted_arr, result - 1);
	init(argc, &sorted_arr, argv, stacks.sa);
	if (check_duplicates(sorted_arr, argc - 1))
		handle_cases(stacks, sorted_arr, &result, argc - 1);
	merge_moves(&result);
	f_lstclear(stacks.sa);
	free_everything(0, stacks, sorted_arr, result - 1);
}

static void	handle_cases(t_stacks stacks, int *sorted_arr, char **result,
unsigned short size)
{
	int	first;
	int	second;
	int	third;

	first = (*stacks.sa)->n;
	second = (*stacks.sa)->next->n;
	if (size == 2)
		if (first > second)
			write(1, "sa\n", 3);
	if (size == 3)
		handle_three(stacks.sa, 'a', result);
	else
	{
		third = (*stacks.sa)->next->next->n;
		if (is_sorted(*stacks.sa, sorted_arr) == 0)
		{
			if (first < second && third < second)
				swap(stacks.sa, 'a', result);
			divide_into_chunks(stacks, sorted_arr, result, size);
			handle_three(stacks.sa, 'a', result);
			while (*stacks.sb)
				push_cheapest(stacks, result);
		}
		adjust(stacks.sa, sorted_arr, result);
	}
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

static void	free_everything(char id, t_stacks stacks, int *sorted_arr,
	char *result)
{
	free(stacks.sa);
	free(stacks.sb);
	free(sorted_arr);
	free(result);
	if (id != 0)
		error(id);
}
