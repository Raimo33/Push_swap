/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:27 by craimond          #+#    #+#             */
/*   Updated: 2023/11/26 12:05:31 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
//#include "push_swap_utils.c"

static void		merge_moves(char **result);
static char		check_duplicates(int *sorted_arr, short size);
static void		handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, short size, char **result);
static char		is_sorted(t_list *stack, int *sorted_arr);
static void		divide_into_chunks(t_list **stack_a, t_list **stack_b, int *sorted_arr, short n_chunks, char **result);
static void		push_easiest(t_list **stack_from, t_list **stack_to,  char **result);
static void		move_to_top(t_list **stack, t_list *node, char ab, char **result);
static void		handle_three(t_list **stack, char ab, char **result);
static t_list	*get_easiest(t_list *stack_from);
static t_list	*get_closest(t_list *stack, int n);
static short	get_distance(t_list *stack, t_list *node);
static void		quicksort(int arr[], int low, int high);
static void		init(int argc, int **sorted_arr, char **argv, t_list **stack_a);
static void		show_moves(int move_counts[], char *moves[]);

// int	main2(int argc, char **argv);

// int	main(void)
// {
//     main2(103, (char *[]){"./push_swap", "10", "98", "66", "40", "56", "94", "81", "42", "99", "8", "34", "54", "100", "36", "22", "24", "65", "37", "2", "64", "38", "80", "49", "83", "51", "45", "7", "55", "72", "85", "23", "92", "82", "68", "88", "89", "43", "50", "6", "73", "70", "14", "29", "32", "35", "30", "41", "59", "33", "25", "76", "84", "12", "58", "77", "60", "20", "63", "19", "91", "74", "78", "31", "1", "15", "87", "62", "48", "47", "18", "69", "27", "11", "75", "44", "3", "46", "28", "26", "39", "97", "79", "61", "96", "16", "52", "57", "95", "21", "86", "17", "4", "67", "53", "90", "5", "13", "93", "71", "9", "1100", "1102"});
// }

int	main(int argc, char **argv)
{
	t_list	**stack_a;
	t_list	**stack_b;
	int		*sorted_arr;
	char	*result;

	if (argc < 3 || !argv || !(*argv))
		error(1);
	result = ft_calloc(20000, sizeof(char));
	sorted_arr = malloc(sizeof(int) * (argc - 1));
	stack_a = malloc(sizeof(t_list *));
	stack_b = malloc(sizeof(t_list *));
	if (!result++ || !stack_a || !stack_b || !sorted_arr)
	{
		free(stack_a);
		free(stack_b);
		free(sorted_arr);
		free(result - 1);
		error(2);
	}
	init(argc, &sorted_arr, argv, stack_a);
	if (check_duplicates(sorted_arr, argc - 1))
		handle_cases(stack_a, stack_b, sorted_arr, argc - 1, &result);
	merge_moves(&result);
	f_lstclear(stack_a);
	free(sorted_arr);
}

static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a)
{
	int	i;
	t_list	*new_node;

	i = 0;
	while(++i < argc)
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

static void	merge_moves(char **result)
{
	char	*start;
	char	*end;
	int		move_counts[5] = {0, 0, 0, 0, 0}; //ra, rb, NULL, rra, rrb
	char 	*moves[10] = {"ra\n", "rb\n", "rr\n", "rra\n", "rrb\n", "rrr\n", "pa\n", "pb\n", "sa\n", "sb\n"};
	
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
	while(i < 5)
	{
		while (move_counts[i] > 0 && move_counts[i + 1] > 0)
		{
			ft_putstr(moves[i + 2]);
			move_counts[i]--;
			move_counts[i + 1]--;
		}
		while(move_counts[i] > 0)
		{
			ft_putstr(moves[i]);
			move_counts[i]--;
		}
		while(move_counts[i + 1] > 0)
		{
			ft_putstr(moves[i + 1]);
			move_counts[i + 1]--;
		}
		i += 3;
	}
}

static char	check_duplicates(int *sorted_arr, short size)
{
	while (--size > 0)
	{
		if (sorted_arr[size - 1] == sorted_arr[size])
			return (0);
	}
	return (1);
}

static void	handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, short size, char **result)
{
	t_list	*min;

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
			while (*stack_b)
				push_easiest(stack_b, stack_a, result);
		}
		min = *stack_a;
		while (min && min->n != sorted_arr[0])
			min = min->next;
		move_to_top(stack_a, min, 'a', result);
	}
}

static char	is_sorted(t_list *stack, int *sorted_arr)
{
	short	i;
	short	arr_len;
	t_list	*tmp;

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

static void	divide_into_chunks(t_list **stack_a, t_list **stack_b, int *sorted_arr, short n_chunks, char **result)
{
	int		i;
	int		j;
	int		key_nbr;
	int		key_nbr2;
	t_list	*node;
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
		while (++i < (arr_len / n_chunks * 2) && (*stack_a)->next->next->next)
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
}

static void	push_easiest(t_list **stack_from, t_list **stack_to,  char **result)
{
	t_list	*tmp_from;
	t_list	*closest_to;
	t_list	*easiest;

	tmp_from = *stack_from;
	while(tmp_from)
	{
		closest_to = get_closest(*stack_to, tmp_from->n);
		tmp_from->easiness = ABS(get_distance(*stack_to, closest_to)) + ABS((get_distance(*stack_from, tmp_from)));
		tmp_from = tmp_from->next;
	}
	easiest = get_easiest(*stack_from);
	move_to_top(stack_to, get_closest(*stack_to, easiest->n), 'a', result);
	move_to_top(stack_from, easiest, 'b', result);
	push(stack_from, stack_to, 'a', result);
}

static void	move_to_top(t_list **stack, t_list *node, char ab, char **result)
{
	if (get_distance(*stack, node) > 0)
	{
		while (*stack != node)
			rotate(stack, ab, result);
		return ;
	}
	while(*stack != node)
		rev_rotate(stack, ab, result);
}

static void	handle_three(t_list **stack, char ab, char **result)
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

static t_list	*get_easiest(t_list *stack_from)
{
	t_list	*easiest;

	easiest = stack_from;
	while (stack_from && easiest->easiness > 1)
	{
		if (stack_from->easiness < easiest->easiness)
			easiest = stack_from;
		stack_from = stack_from->next;
	}
	return (easiest);
}

static t_list	*get_closest(t_list *stack, int n)
{
	int		best_n;
	t_list	*closest;

	best_n = INT_MAX;
	closest = NULL;
	while(stack)
	{
		if (n - stack->n < 0 && n - stack->n > n - best_n)
		{
			best_n = stack->n;
			closest = stack;
		}
		stack = stack->next;
	}
	return (closest);
}

static short	get_distance(t_list *stack, t_list *node)
{
	int dist;
	int	len;

	len = lst_len(stack);
	dist = 0;
	while (stack != node && ++dist)
		stack = stack->next;
	if (dist > len / 2)
		return ((len - dist) * -1);
	return(dist);
}

static void	quicksort(int arr[], int low, int high)
{
	int pivot;
	int i;
	int j;
	int temp;

    if (low < high) 
	{
        pivot = arr[high];
        i = low;
        j = low - 1;
        while (++j < high) 
		{
            if (arr[j] < pivot) 
			{
                temp = arr[i];
                arr[i++] = arr[j];
                arr[j] = temp;
            }
        }
        temp = arr[i];
        arr[i] = arr[high];
        arr[high] = temp;
        quicksort(arr, low, i - 1);
        quicksort(arr, i + 1, high);
    }
}

