/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:28:51 by craimond          #+#    #+#             */
/*   Updated: 2023/11/23 12:13:28 by craimond         ###   ########.fr       */
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

typedef	struct s_list
{
	int				n;
	short			easiness;
	struct s_list	*next;
}					t_list;

void	swap(t_list **stack, char ab);
void	push(t_list **stack_from, t_list **stack_to, char ab);
void	rotate(t_list **stack, char ab);
void	rev_rotate(t_list **stack, char ab);
short	lst_len(t_list *lst);
t_list	*f_lstnew(int n);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		f_lstclear(t_list **lst);
int		ft_atoi(const char *str);

#endif