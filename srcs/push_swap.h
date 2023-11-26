/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:28:51 by craimond          #+#    #+#             */
/*   Updated: 2023/11/26 12:09:37 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

# define FIRST(a) ((a)->n)
# define SECOND(a) ((a)->next->n)
# define THIRD(a) ((a)->next->next->n)
# define ABS(value) (((value < 0) * -1 * value) + (value * (value >= 0)))
# define N_CHUNKS(n) ((n > 500) * 8 + (n >= 100 && n <= 500) * 4 + (n < 100) * 2)
# define HIGHEST(n1, n2) ((n1 > n2) * n1 + (n1 < n2) * n2)

typedef	struct s_list
{
	int				n;
	short			easiness;
	struct s_list	*next;
}						t_list;

void	swap(t_list **stack, char ab, char **result);
void	push(t_list **stack_from, t_list **stack_to, char ab, char **result);
void	rotate(t_list **stack, char ab, char **result);
void	rev_rotate(t_list **stack, char ab, char **result);
short	lst_len(t_list *lst);
t_list	*f_lstnew(int n);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		f_lstclear(t_list **lst);
int		ft_atoi(const char *str);
void	*ft_calloc(size_t nmemb, size_t size);
void	ft_putstr(char *s);
void	*ft_memset(void *s, int c, size_t n);
void	error(char id);

#endif