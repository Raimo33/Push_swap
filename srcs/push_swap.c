/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:27 by craimond          #+#    #+#             */
/*   Updated: 2023/11/29 15:36:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// #include "a_to_b.c"
// #include "b_to_a.c"
// #include "general_utils.c"
// #include "lst_utils.c"
// #include "display.c"
// #include "stack_operations.c"
// int	main2(int argc, char **argv);

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a);
static char	check_duplicates(int *sorted_arr, short size);
static void	handle_cases(t_stacks stacks, int *sorted_arr, char **result, unsigned short size);
static char	is_sorted(t_list *stack, int *sorted_arr);

// int main(void)
// {
//     char *numbers[] = {"./push_swap", "354", "369", "39", "491", "390", "190", "66", "343", "21", "2147483647", "-2147483648", "348", "85", "200", "372"};
//     main2(16, numbers);
// }

int	main(int argc, char **argv)
{
	char		buffer[N_MOVES];
	t_stacks	stacks;
	int			*sorted_arr;
	char		*result;

	if (argc < 3 || !argv || !(*argv))
		return (0);
	result = buffer;
	sorted_arr = malloc(sizeof(int) * (argc - 1));
	stacks.sa = malloc(sizeof(t_list *));
	stacks.sb = malloc(sizeof(t_list *));
	*(stacks.sa) = 0;
	*(stacks.sb) = 0;
	if (!result++ || !stacks.sa || !stacks.sb || !sorted_arr)
		error(1);
	init(argc, &sorted_arr, argv, stacks.sa);
	if (check_duplicates(sorted_arr, argc - 1))
		handle_cases(stacks, sorted_arr, &result, argc - 1);
	merge_moves(&result);
	f_lstclear(stacks.sa);
	//f_lstclear(stacks.sb);
	free(sorted_arr);
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

static void	handle_cases(t_stacks stacks, int *sorted_arr, char **result, unsigned short size)
{
	t_list	*min;

	if (size == 2 && (*(stacks.sa))->n > (*(stacks.sa))->next->n)
		write(1, "sa\n", 3);
	else if (size == 3)
		handle_three(stacks.sa, 'a', result);
	else
	{
		if (is_sorted(*(stacks.sa), sorted_arr) == 0)
		{
			divide_into_chunks(stacks, sorted_arr, result, size);
			handle_three(stacks.sa, 'a', result);
			while (*(stacks.sb))
				push_easiest(stacks, result);
		}
		adjust(stacks.sa, sorted_arr, result);
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
