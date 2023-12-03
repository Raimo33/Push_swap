/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:27 by craimond          #+#    #+#             */
/*   Updated: 2023/12/03 19:22:19 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// #include "a_to_b.c"
// #include "b_to_a.c"
// #include "display.c"
// #include "stack_operations.c"
// #include "macros.c"
// #include "general_utils.c"

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a);
static char	check_duplicates(int *sorted_arr, short size);
static void	free_everything(t_stacks stacks, int *sorted_arr,
	char *result, char **argv);
static void	handle_cases(t_stacks stacks, int *sorted_arr, char **result,
				unsigned short size);

// int	main(void)
// {
// 	main2(4, (char *[]){"./push_swap", "2147483645", "2147483646", "2147483647"});
// }

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	int			*sorted_arr;
	char		*result;

	argv = handle_split(&argc, argv);
	if (argc <= 2)
	{
		if (argv[1])
			f_atol(argv[1]);
		return (0);
	}
	result = ft_calloc(N_MOVES, sizeof(char));
	sorted_arr = ft_calloc(argc - 1, sizeof(int));
	stacks.sa = ft_calloc(1, sizeof(t_list *));
	stacks.sb = ft_calloc(1, sizeof(t_list *));
	if (!result++ || !stacks.sa || !stacks.sb || !sorted_arr)
		error(1);
	init(argc, &sorted_arr, argv, stacks.sa);
	if (check_duplicates(sorted_arr, argc - 1))
		handle_cases(stacks, sorted_arr, &result, argc - 1);
	merge_moves(&result);
	free_everything(stacks, sorted_arr, result - 1, argv);
}

static void	handle_cases(t_stacks stacks, int *sorted_arr, char **result,
unsigned short size)
{
	int	first;
	int	second;
	int	third;

	first = (*stacks.sa)->n;
	second = (*stacks.sa)->next->n;
	if (size == 2 && first > second)
		write(1, "sa\n", 3);
	else if (size == 3)
		handle_three(stacks.sa, 'a', result);
	else if (size > 3)
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

static void	free_everything(t_stacks stacks, int *sorted_arr,
	char *result, char **argv)
{
	f_lstclear(stacks.sa);
	free(stacks.sa);
	free(stacks.sb);
	free(sorted_arr);
	free(result);
	//fare un check per capire se e' stata allocata dinamicamente o staticamente
	free_matrix(argv);
}
