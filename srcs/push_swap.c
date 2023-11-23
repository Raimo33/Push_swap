/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:27 by craimond          #+#    #+#             */
/*   Updated: 2023/11/23 12:36:24 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
//#include "push_swap_utils.c"

static char		check_duplicates(int *sorted_arr, short size);
static void		handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, short size);
static void		divide_into_chunks(t_list **stack_a, t_list **stack_b, int *sorted_arr, short n_chunks);
static void		push_last_chunk(t_list **stack_a, t_list **stack_b);
static void		push_easiest(t_list **stack_from, t_list **stack_to);
static void		move_to_top(t_list **stack, t_list *node, char ab);
static void		handle_three(t_list **stack, char ab);
static t_list	*get_easiest(t_list *stack_from);
static t_list	*get_closest(t_list *stack, int n);
static short	get_distance(t_list *stack, t_list *node);
static void		quicksort(int arr[], int low, int high);

// int	main(void)
// {
//     main2(101, (char *[]){"./push_swap", "85", "107", "85", "17", "66", "46", "39", "6", "80", "55", "78", "77", "69", "43", "36", "29", "41", "90", "108", "38", "81", "53", "27", "104", "1", "47", "42", "94", "71", "21", "70", "23", "64", "89", "30", "110", "10", "20", "15", "32", "28", "87", "60", "76", "74", "102", "83", "88", "49", "98", "40", "51", "61", "93", "106", "45", "11", "31", "73", "91", "13", "79", "72", "37", "26", "8", "48", "2", "50", "5", "56", "57", "44", "59", "54", "22", "58", "95", "63", "52", "7", "84", "92", "25", "34", "75", "86", "101", "103", "12", "100", "82", "16", "35", "96", "14", "18", "24", "19", "99", "4", "62", "109", "105", "9", "97", "65", "68", "3", "67"});
// }

int	main(int argc, char **argv)
{
	t_list	**stack_a;
	t_list	**stack_b;
	t_list	*new_node;
	int		i;
	int		*sorted_arr;

	if (argc < 3 || !argv || !(*argv))
		return (0);
	sorted_arr = malloc(sizeof(int) * (argc - 1));
	stack_a = malloc(sizeof(t_list *));
	stack_b = malloc(sizeof(t_list *));
	if (!stack_a || !stack_b || !sorted_arr)
	{
		free(stack_a);
		free(stack_b);
		free(sorted_arr);
		return (0);
	}
	i = 0;
	while(++i < argc)
		sorted_arr[i - 1] = ft_atoi(argv[i]);
	while (--i > 0) 
	{
		new_node = f_lstnew(sorted_arr[i - 1]);
		if (!new_node)
			return (f_lstclear(stack_a));
		ft_lstadd_front(stack_a, new_node);
	}
	quicksort(sorted_arr, 0, argc - 2);
	if (check_duplicates(sorted_arr, argc - 1))
		handle_cases(stack_a, stack_b, sorted_arr, argc - 1);
	f_lstclear(stack_a);
	free(sorted_arr);
	return (0);
}

static char	check_duplicates(int *sorted_arr, short size)
{
	int i;

	i = -1;
	while (++i < size - 1)
	{
		if (sorted_arr[i] == sorted_arr[i + 1])
			return (0);
	}
	return (1);
}

static void	handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, short size)
{
	int		i;
	t_list	*min;

	i = -1;
	if (size == 2 && (*stack_a)->n > (*stack_a)->next->n)
		write(1, "sa\n", 3);
	else if (size == 3)
		handle_three(stack_a, 'a');
	else
	{
		if (size < 10)
			divide_into_chunks(stack_a, stack_b, sorted_arr, 2);
		else
			divide_into_chunks(stack_a, stack_b, sorted_arr, 4 * (2 - (size <= 100)));
		handle_three(stack_a, 'a');
		while (*stack_b)
			push_easiest(stack_b, stack_a);
		min = *stack_a;
		while (min && min->n != sorted_arr[0])
			min = min->next;
		move_to_top(stack_a, min, 'a');
	}
}

static void	divide_into_chunks(t_list **stack_a, t_list **stack_b, int *sorted_arr, short n_chunks)
{
	int		i;
	int		j;
	int		key_nbr;
	t_list	*node;
	int		arr_len;

	j = 0;
	arr_len = lst_len(*stack_a);
	node = *stack_a;
	while (++j <= n_chunks - 1)
	{
		key_nbr = sorted_arr[(arr_len / n_chunks) * j - 1];
		i = -1;
		while (++i < (arr_len / n_chunks) && node)
		{
			while (node && node->n > key_nbr)
				node = node->next;
			move_to_top(stack_a, node, 'a');
			push(stack_a, stack_b, 'b');
			node = *stack_a;
		}
	}
	push_last_chunk(stack_a, stack_b);
}

static void	push_last_chunk(t_list **stack_a, t_list **stack_b)
{
	t_list	*max;
	t_list	*node;

	max = *stack_a;
	node = *stack_a;
	while(node)
	{
		if (node->n > max->n)
			max = node;
		node = node->next;
	}
	while((*stack_a)->next->next->next)
	{
		if (*stack_a == max)
			rotate(stack_a, 'a');
		push(stack_a, stack_b, 'b');
	}
}

static void	push_easiest(t_list **stack_from, t_list **stack_to)
{
	t_list	*tmp_from;
	t_list	*closest_to;
	t_list	*easiest;
	short	size_to;
	short	size_from;

	tmp_from = *stack_from;
	size_to = lst_len(*stack_to);
	size_from = lst_len(*stack_from);
	while(tmp_from)
	{
		closest_to = get_closest(*stack_to, tmp_from->n);
		tmp_from->easiness = ABS((size_to * (get_distance(*stack_to, closest_to) > size_to / 2) - get_distance(*stack_to, closest_to)));
		tmp_from->easiness += ABS((size_from * (get_distance(*stack_from, tmp_from) > size_from / 2) - get_distance(*stack_from, tmp_from)));
		if (tmp_from->easiness <= 1)
			break ;
		tmp_from = tmp_from->next;
	}
	easiest = get_easiest(*stack_from);
	move_to_top(stack_to, get_closest(*stack_to, easiest->n), 'a');
	move_to_top(stack_from, easiest, 'b');
	push(stack_from, stack_to, 'a');
	//dopo combino le mosse rrr unendo ogni coppia di rra e rrb e ra rb che occorra prima del PUSH
}

static void	move_to_top(t_list **stack, t_list *node, char ab)
{
	if (get_distance(*stack, node) < lst_len(*stack) / 2)
	{
		while (*stack != node)
			rotate(stack, ab);
		return ;
	}
	while(*stack != node)
		rev_rotate(stack, ab);
}

static	void adjust(t_list *stack)
{
	
}

static void	handle_three(t_list **stack, char ab)
{
	if (FIRST(*stack) > SECOND(*stack) && SECOND(*stack) < THIRD(*stack) && FIRST(*stack) < THIRD(*stack)) //[2,1,3]
		swap(stack, ab);
	else if (FIRST(*stack) > SECOND(*stack) && SECOND(*stack) > THIRD(*stack)) //[3,2,1]
	{
		swap(stack, ab);
		rev_rotate(stack, ab);
	}
	else if (FIRST(*stack) > SECOND(*stack) && SECOND(*stack) < THIRD(*stack)) //[3,1,2]
		rotate(stack, ab);
	else if (FIRST(*stack) < SECOND(*stack) && SECOND(*stack) > THIRD(*stack) && FIRST(*stack) < THIRD(*stack)) //[1,3,2]
	{
		swap(stack, ab);
		rotate(stack, ab);
	}
	else if (FIRST(*stack) < SECOND(*stack) && SECOND(*stack) > THIRD(*stack)) //[2,3,1]
		rev_rotate(stack, ab);
}

static t_list	*get_easiest(t_list *stack_from)
{
	t_list *easiest;

	easiest = stack_from;
	while (stack_from)
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
	closest = stack;
	while(stack)
	{
		if (n - stack->n < 0 && n - stack->n > n - best_n)
			best_n = stack->n;
		stack = stack->next;
	}
	while(closest)
	{
		if (closest->n == best_n)
			break ;
		closest = closest->next;
	}
	return (closest);
}

static short	get_distance(t_list *stack, t_list *node)
{
	int dist;

	dist = 0;
	while (stack != node)
	{
		dist++;
		stack = stack->next;
	}
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
        j = low;
        while (j < high) 
		{
            if (arr[j] < pivot) 
			{
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                i++;
            }
            j++;
        }
        temp = arr[i];
        arr[i] = arr[high];
        arr[high] = temp;
        quicksort(arr, low, i - 1);
        quicksort(arr, i + 1, high);
    }
}
