/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:20:12 by craimond          #+#    #+#             */
/*   Updated: 2023/11/26 12:18:25 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	ft_isspace(const char c);

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

void	error(char id)
{
	write(2, "Error\n", 6);
	exit(id);
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
