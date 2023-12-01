/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:31:23 by craimond          #+#    #+#             */
/*   Updated: 2023/12/01 16:46:56 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CHECKER_BONUS_H
# define CHECKER_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>

# ifndef BUFFFER_SIZE
#  define BUFFER_SIZE 4
# endif

# include "get_next_line/get_next_line.h"

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

char	rotate(t_list **stack);
char	rev_rotate(t_list **stack);
char	push(t_list **stack_from, t_list **stack_to);
char	swap(t_list **stack);
void	quicksort(int arr[], int low, int high);
void	free_everything(char id, t_stacks stacks, int *sorted_arr);
char	scmp(char *s1, char *s2);
long	f_atol(char *nptr);
void	error(char id);
t_list	*f_lstnew(int n);
void	ft_lstadd_front(t_list **lst, t_list *new);
void	f_lstclear(t_list **lst);

#endif