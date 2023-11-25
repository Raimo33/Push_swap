/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:20:12 by craimond          #+#    #+#             */
/*   Updated: 2023/11/25 19:22:32 by craimond         ###   ########.fr       */
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

void	swap(t_list **stack, char ab, char **result)
{
	t_list	*first;
	t_list	*second;

	if (stack && *stack && (*stack)->next)
	{
		first = *stack;
		second = first->next;
		first->next = second->next;
		second->next = first;
		*stack = second;
	}
	if (ab == 'a')
		**result = 9;
	else
		**result = 10;
	(*result)++;
}
void	push(t_list **stack_from, t_list **stack_to, char ab, char **result)
{
	t_list	*tmp;

	if (stack_to && stack_from && *stack_from)
	{
        tmp = *stack_from;
        *stack_from = (*stack_from)->next;
        tmp->next = *stack_to;
        *stack_to = tmp; 
	}
	if (ab == 'a')
		**result = 7;
	else
		**result = 8;
	(*result)++;
}

void	rotate(t_list **stack, char ab, char **result)
{
	t_list	*first;
	t_list	*tmp;

	if (stack && *stack && (*stack)->next)
	{
		first = *stack;
		*stack = first->next;
		tmp = *stack;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = first;
		first->next = NULL;
	}
	if (ab == 'a')
		**result = 1;
	else
		**result = 2;
	(*result)++;
}

void	rev_rotate(t_list **stack, char ab, char **result)
{
	t_list	*last;
	t_list	*tmp;

	if (stack && *stack && (*stack)->next)
	{
		tmp = *stack;
		while (tmp->next->next)
			tmp = tmp->next;
		last = tmp->next;
		last->next = *stack;
		tmp->next = NULL;
		*stack = last;
	}
	if (ab == 'a')
		**result = 4;
	else
		**result = 5;
	(*result)++;
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

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;

	if (nmemb != 0 && size > ULONG_MAX / nmemb)
		return (NULL);
	arr = (void *)malloc(size * nmemb);
	if (arr == NULL)
		return (NULL);
	while (size-- > 0)
		((char *)arr)[size] = '\0';
	((char *)arr)[0] = '\0';
	return (arr);
}

void	ft_putstr(char *s)
{
	while (*s != '\0')
		write(1, s++, 1);
}

