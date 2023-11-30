/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:28:51 by craimond          #+#    #+#             */
/*   Updated: 2023/11/30 13:18:21 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
# include <limits.h>

# ifndef N_MOVES
#  define N_MOVES 20000
# endif

typedef struct s_list
{
	int				n;
	short			dist;
	short			easiness;
	struct s_list	*brother;
	struct s_list	*next;
}						t_list;

typedef struct s_stacks
{
	t_list	**sa;
	t_list	**sb;
}				t_stacks;

struct s_keynbrs
{
	int	n1;
	int	n2;
};

char			is_sorted(t_list *stack, int *sorted_arr);
void			divide_into_chunks(t_stacks stacks, int *sorted_arr,
					char **result, unsigned short size);
void			handle_three(t_list **stack, char ab, char **result);
void			push_easiest(t_stacks stacks, char **result);
void			adjust(t_list **stack_a, int *sorted_arr, char **result);
void			merge_moves(char **result);
void			rotate(t_list **stack, char ab, char **result);
void			rev_rotate(t_list **stack, char ab, char **result);
void			push(t_list **stack_from, t_list **stack_to, char ab,
					char **result);
void			swap(t_list **stack, char ab, char **result);
void			move_to_top(t_list **stack, t_list *node, char ab,
					char **result);
t_list			*f_lstnew(int n);
void			ft_lstadd_front(t_list **lst, t_list *new);
void			f_lstclear(t_list **lst);
short			lst_len(t_list *lst);
void			reset_distances(t_list *stack);
void			*ft_calloc(size_t nmemb, size_t size);
void			ft_putstr(char *s);
void			error(char id);
long			f_atol(char *nptr);
void			quicksort(int arr[], int low, int high);

unsigned char	get_n_chunks(short n);
int				abs(int n);

#endif