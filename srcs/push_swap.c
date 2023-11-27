/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:27 by craimond          #+#    #+#             */
/*   Updated: 2023/11/27 17:44:27 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// #include "a_to_b.c"
// #include "b_to_a.c"
// #include "general_utils.c"
// #include "lst_utils.c"
// #include "display.c"
// #include "stack_operations.c"

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a);
static char	check_duplicates(int *sorted_arr, short size);
static void	handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, char **result);
static char	is_sorted(t_list *stack, int *sorted_arr);

// int	main(void)
// {
//     main2(6, (char *[]){"./push_swap", "-1", "3", "0", "2", "1"});
// }

int	main(int argc, char **argv)
{
	char	buffer[N_MOVES];
	t_list	**stack_a;
	t_list	**stack_b;
	int		*sorted_arr;
	char	*result;

	if (argc < 3 || !argv || !(*argv))
		return (0);
	result = buffer;
	sorted_arr = malloc(sizeof(int) * (argc - 1));
	stack_a = malloc(sizeof(t_list *));
	stack_b = malloc(sizeof(t_list *));
	if (!result++ || !stack_a || !stack_b || !sorted_arr)
		error(2);
	init(argc, &sorted_arr, argv, stack_a);
	if (check_duplicates(sorted_arr, argc - 1))
		handle_cases(stack_a, stack_b, sorted_arr, &result);
	merge_moves(&result);
	f_lstclear(stack_a);
	free(sorted_arr);
}

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a)
{
	t_list	*new_node;
	int		i;

	i = 0;
	while (++i < argc)
		(*sorted_arr)[i - 1] = ft_atoi(argv[i]);
	while (--i > 0)
	{
		new_node = f_lstnew((*sorted_arr)[i - 1]);
		if (!new_node)
			error(2);
		ft_lstadd_front(stack_a, new_node);
	}
	quicksort((*sorted_arr), 0, argc - 2);
}

static char	check_duplicates(int *sorted_arr, short size)
{
	while (--size > 0)
		if (sorted_arr[size - 1] == sorted_arr[size])
			return (0);
	return (1);
}

static void	handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, char **result)
{
	t_list	*min;
	int		key_nbr;
	short	i;
	short	j;
	short	size;

	size = lst_len(*stack_a);
	if (size == 2 && (*stack_a)->n > (*stack_a)->next->n)
		write(1, "sa\n", 3);
	else if (size == 3)
		handle_three(stack_a, 'a', result);
	else
	{
		if (is_sorted(*stack_a, sorted_arr) == 0)
		{
			divide_into_chunks(stack_a, stack_b, sorted_arr, N_CHUNKS(size), result);
			handle_three(stack_a, 'a', result);
			i = SHRT_MAX - 1;
			j = N_CHUNKS(size);
			while (*stack_b)
			{
				if (++i >= size / N_CHUNKS(size))
				{
					key_nbr = sorted_arr[size / N_CHUNKS(size) * --j - 2];
					i = -1;
				}
				push_easiest(stack_b, stack_a, key_nbr, result);
			}
		}
		adjust(stack_a, sorted_arr, result);
	}
}

static char	is_sorted(t_list *stack, int *sorted_arr)
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
