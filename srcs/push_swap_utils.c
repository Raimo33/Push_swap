/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:20:12 by craimond          #+#    #+#             */
/*   Updated: 2023/11/21 15:52:32 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_isspace(const char c);

int	f_lstclear(t_list **lst)
{
	if (*lst == NULL || lst == NULL)
		return (0);
	if ((*lst)->next != NULL)
		f_lstclear(&(*lst)->next);
	free(*lst);
	*lst = NULL;
	return (0);
}

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}

t_list	*f_lstnew(int n)
{
	t_list	*new_node;

	new_node = malloc(sizeof(t_list));
	if (new_node == NULL)
		return (NULL);
	new_node->n = n;
	new_node->easiness = SHRT_MAX;
	new_node->next = NULL;
	return (new_node);
}
short	lst_len(t_list *lst)
{
	int	len;

	len = 0;
	while (lst)
	{
		len++;
		lst = lst->next;
	}
	return (len);
}

void	swap(t_list **head, char ab)
{
	t_list	*first;
	t_list	*second;

	if (head && *head && (*head)->next)
	{
		first = *head;
		second = first->next;
		first->next = second->next;
		second->next = first;
		*head = second;
	}
	write(1, "s", 1);
	write(1, &ab, 1);
	write(1, "\n", 1);
}
void	push(t_list **head_to, t_list **head_from, char ab)
{
	t_list	*tmp;

	if (head_to && head_from && *head_from)
	{
        tmp = *head_from;
        *head_from = (*head_from)->next;
        tmp->next = *head_to;
        *head_to = tmp; 
	}
	write(1, "p", 1);
	write(1, &ab, 1);
	write(1, "\n", 1);
}

void	rotate(t_list **head, char ab)
{
	t_list	*first;
	t_list	*tmp;

	if (head && *head && (*head)->next)
	{
		first = *head;
		*head = first->next;
		tmp = *head;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = first;
		first->next = NULL;
	}
	write(1, "r", 1);
	write(1, &ab, 1);
	write(1, "\n", 1);
}

void	rev_rotate(t_list **head, char ab)
{
	t_list	*last;
	t_list	*tmp;

	if (head && *head && (*head)->next)
	{
		tmp = *head;
		while (tmp->next->next)
			tmp = tmp->next;
		last = tmp->next;
		last->next = *head;
		tmp->next = NULL;
		*head = last;
	}
	write(1, "rr", 2);
	write(1, &ab, 1);
	write(1, "\n", 1);
}

int	ft_atoi(const char *nptr)
{
	int	n;
	int	sign;

	n = 0;
	sign = 1;
	while (ft_isspace(*nptr) == 1)
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	while (*nptr <= '9' && *nptr >= '0')
	{
		n *= 10;
		n += (*nptr - 48);
		nptr++;
	}
	return (n * sign);
}

static int	ft_isspace(const char c)
{
	if (c == 32 || (c >= '\t' && c <= '\r'))
		return (1);
	return (0);
}
