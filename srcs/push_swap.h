/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 12:28:51 by craimond          #+#    #+#             */
/*   Updated: 2023/11/21 16:31:40 by craimond         ###   ########.fr       */
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

typedef	struct s_list
{
	int				n;
	short			easiness;
	struct s_list	*next;
}					t_list;

t_list	*f_lstnew(int n);
void	ft_lstadd_front(t_list **lst, t_list *new);
int		f_lstclear(t_list **lst);
short	lst_len(t_list *lst);
void	swap(t_list **head, char ab);
void	push(t_list **head_to, t_list **head_from, char ab);
void	rotate(t_list **head, char ab);
void	rev_rotate(t_list **head, char ab);
int		ft_atoi(const char *nptr);

#endif