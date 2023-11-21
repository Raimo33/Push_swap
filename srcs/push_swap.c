/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:26:27 by craimond          #+#    #+#             */
/*   Updated: 2023/11/21 15:07:38 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"
//#include "push_swap_utils.c"

static void	handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, int size);
static void	get_extremes(t_list **stack_to, t_list **stack_from, int quantity, short flag);
static void	divide_into_chunks(t_list **stack_a, t_list **stack_b, int *sorted_arr, short n_chunks);
static void	divide_into_chunks(t_list **stack_a, t_list **stack_b, int *sorted_arr, short n_chunks);
static void	push_easiest(t_list **stack_from, t_list **stack_to, short flag_ab);
static void	move_item(t_list **stack_from, t_list **stack_to, t_list *node, short flag_ab);
static void	move_to_top(t_list **stack, t_list *node, char ab);
static void	handle_three(t_list **stack, char ab);
static t_list	*get_easiest(t_list *stack_from);
static t_list	*get_closest(t_list *stack, int n);
static short	get_easiness(t_list *stack, t_list *node, short size);
static short	get_distance(t_list *stack, t_list *node);
static void	quicksort(int arr[], int low, int high);

// int	main(void)
// {
//     main2(11, (char *[]){"./push_swap", "6", "9", "10", "3", "7", "5", "2", "1", "4", "8"});
// }

int	main(int argc, char **argv)
{
	t_list	**stack_a;
	t_list	**stack_b;
	t_list	*new_node;
	int		i;
	int		*sorted_arr;

	if (argc < 1 || !argv || !(*argv))
		return (0);
	else if (argc == 2 && ft_atoi(argv[1]) > ft_atoi(argv[2]))
		write(1, "sa\n", 3);
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
		new_node = f_lstnew(sorted_arr[i - 1]); //RIEMPIO LA LISTA 1 DI TROPPO
		if (!new_node)
			return (f_lstclear(stack_a));
		ft_lstadd_front(stack_a, new_node);
	}
	handle_cases(stack_a, stack_b, sorted_arr, argc - 1);
	return (0);
}

static void	handle_cases(t_list **stack_a, t_list **stack_b, int *sorted_arr, int size)
{
	int	i;

	i = -1;
	quicksort(sorted_arr, 0, size - 1);
	if (size == 3)
		handle_three(stack_a, 'a');
	if (size < 10)
	{
		get_extremes(stack_b, stack_a, size - 3, 1);
		handle_three(stack_a, 'a');
		while (--size >= 3)
			push(stack_a, stack_b, 'a');
	}
	else if (size >= 10)
	{
		divide_into_chunks(stack_a, stack_b, sorted_arr, 4 * (2 - (size <= 100)));
		handle_three(stack_a, 'a');
		while (*stack_b)
			push_easiest(stack_b, stack_a, -1);
	}
}

static void	get_extremes(t_list **stack_to, t_list **stack_from, int quantity, short flag)
{
	t_list	*node;
	t_list	*extreme;
	int		i;

	i = -1;
	while (++i < quantity)
	{
		node = *stack_from;
		extreme = *stack_from;
		while (node)
		{
			if (flag == 1)
			{
				if (node->n < extreme->n)
					extreme = node;
			}
			else if (flag == -1)
			{
				if (node->n > extreme->n)
					extreme = node;
			}
			node = node->next;
		}
		move_item(stack_from, stack_to, extreme, flag);
	}
}

static void	divide_into_chunks(t_list **stack_a, t_list **stack_b, int *sorted_arr, short n_chunks)
{
	int		i;
	int		j;
	int		key_nbr;
	t_list	*node;
	t_list	*max;
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
			move_item(stack_a, stack_b, node, 1);
			node = *stack_a;
		}
	}
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
		if (*stack_a != max)
			push(stack_b, stack_a, 'b');
		else
			push(&(*stack_a)->next, stack_a,  'b');
	}
}

static void	push_easiest(t_list **stack_from, t_list **stack_to, short flag_ab)
{
	t_list	*tmp_from;
	t_list	*tmp_to;
	t_list	*closest_to;
	t_list	*easiest;
	short	size_to;
	short	size_from;

	tmp_from = *stack_from;
	tmp_to = *stack_to;
	size_to = lst_len(*stack_to);
	size_from = lst_len(*stack_from);
	while(tmp_from)
	{
		tmp_to = *stack_to;
		closest_to = get_closest(tmp_to, tmp_from->n);
		tmp_from->easiness = get_easiness(*stack_to, closest_to, size_to) + get_easiness(*stack_from, tmp_from, size_from);
		tmp_from = tmp_from->next;
	}
	easiest = get_easiest(*stack_from);
	move_to_top(stack_to, get_closest(*stack_to, easiest->n), 'a');
	move_item(stack_from, stack_to, easiest, flag_ab);
	//dopo combino le mosse rrr unendo ogni coppia di rra e rrb e ra rb che occorra prima del PUSH
}

static void	move_item(t_list **stack_from, t_list **stack_to, t_list *node, short flag_ab)
{
	int		len;
	int		distance;
	int		k;
	char	ab[] = {'a', 'b'};

	len = lst_len(*stack_from);
	distance = get_distance(*stack_from, node);
	if (distance <= len / 2)
	{
		k = distance;
		while (--k >= 0)
			rotate(stack_from, ab[flag_ab == -1]);
		push(stack_to, stack_from, ab[flag_ab == 1]);
	}
	else
	{
		k = len - distance;
		while (--k >= 0)
			rev_rotate(stack_from, ab[flag_ab == -1]);
		push(stack_to, stack_from, ab[flag_ab == 1]);
	}
}

static void	move_to_top(t_list **stack, t_list *node, char ab)
{
	if (get_distance(*stack, node) < lst_len(*stack) / 2)
	{
		while (*stack != node)
			rotate(stack, ab);
	}
	else
	{
		while(*stack != node)
			rev_rotate(stack, ab);
	}
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
	t_list	*closest;

	closest = stack;
	while(stack)
	{
		if (n - stack->n <= 0 && (n - stack->n >= n - closest->n))
			closest = stack;
		stack = stack->next;
	}
	return (closest);
}

static short	get_easiness(t_list *stack, t_list *node, short size)
{
	short	distance;

	distance = get_distance(stack, node);
	if (distance > size / 2)
		distance = (size - distance);
	return (distance);
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
