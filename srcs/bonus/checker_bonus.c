/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:31:26 by craimond          #+#    #+#             */
/*   Updated: 2023/12/01 17:03:25 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static char	check_duplicates(int *sorted_arr, short size);
static void	check_sorting(t_list *stack_a, t_list *stack_b);
static void	init(int argc, int **sorted_arr, char **argv, t_list **stack_a);
static void	make_move(t_stacks stacks, char **ln);

int	main(int argc, char **argv)
{
	t_stacks	stacks;
	int			*sorted_arr;
	char		*ln;

	if (argc < 3)
	{
		if (argv[1])
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
	ln = get_next_line(0);
	while (ln)
		make_move(stacks, &ln);
	check_sorting(*stacks.sa, *stacks.sb);
	f_lstclear(stacks.sa);
	free_everything(0, stacks, sorted_arr);
}

static void	make_move(t_stacks stacks, char **ln)
{
	if (scmp(*ln, "ra\n") || scmp(*ln, "rb\n"))
		rotate((t_list **)(((uintptr_t)(stacks.sa)) * scmp(*ln, "ra\n")
				+ ((uintptr_t)(stacks.sb)) * scmp(*ln, "rb\n")));
	else if (scmp(*ln, "rra\n") || scmp(*ln, "rrb\n"))
		rev_rotate((t_list **)(((uintptr_t)(stacks.sa)) * scmp(*ln, "rra\n")
				+ ((uintptr_t)(stacks.sb)) * scmp(*ln, "rrb\n")));
	else if (scmp(*ln, "pa\n") || scmp(*ln, "pb\n"))
		push((t_list **)(((uintptr_t)(stacks.sa)) * scmp(*ln, "pb\n")
				+ ((uintptr_t)(stacks.sb)) * scmp(*ln, "pa\n")),
			(t_list **)(((uintptr_t)(stacks.sa)) * (scmp(*ln, "pa\n"))
				+ ((uintptr_t)(stacks.sb)) * scmp(*ln, "pb\n")));
	else if (scmp(*ln, "rr\n"))
		(void)(rotate(stacks.sa) + rotate(stacks.sb));
	else if (scmp(*ln, "rrr\n"))
		(void)(rev_rotate(stacks.sa) + rev_rotate(stacks.sb));
	else if (scmp(*ln, "sa\n") || scmp(*ln, "sb\n"))
		swap((t_list **)(((uintptr_t)stacks.sa) * scmp(*ln, "sa\n")
				+ ((uintptr_t)stacks.sb) * scmp(*ln, "sb\n")));
	else if (scmp(*ln, "ss\n"))
		(void)(swap(stacks.sa) + swap(stacks.sb));
	else
		error(2);
	free(*ln);
	*ln = get_next_line(0);
}

static void	check_sorting(t_list *stack_a, t_list *stack_b)
{
	if (stack_b)
	{
		write(1, "KO\n", 3);
		return ;
	}
	while (stack_a->next)
	{
		if (stack_a->n > stack_a->next->n)
		{
			write(1, "KO\n", 3);
			return ;
		}
		stack_a = stack_a->next;
	}
	if (!stack_a->next)
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
