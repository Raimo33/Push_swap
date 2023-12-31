/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:20:12 by craimond          #+#    #+#             */
/*   Updated: 2023/12/04 14:12:38 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	n;

	if (nmemb != 0 && size > ULONG_MAX / nmemb)
		return (NULL);
	arr = (void *)malloc(size * nmemb);
	if (arr == NULL)
		return (NULL);
	n = size * nmemb;
	while (n-- > 0)
		((char *)arr)[n] = '\0';
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

long	f_atol(char *nptr)
{
	long	n;
	char	sign;

	n = 0;
	while (*nptr == 32 || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	sign = nptr[0];
	if (*nptr == '-' || *nptr == '+')
		nptr++;
	if (*nptr > '9' || *nptr < '0')
		error(2);
	while (*nptr != '\0' && *nptr <= '9' && *nptr >= '0')
	{
		n *= 10;
		n += (*nptr - 48);
		nptr++;
	}
	n = (-n) * (sign == '-') + (n) * (sign != '-');
	if (*nptr != '\0' || n > INT_MAX || n < INT_MIN)
		error(2);
	return (n);
}

void	quicksort(int arr[], int low, int high)
{
	int	pivot;
	int	i;
	int	j;
	int	temp;

	if (low < high)
	{
		pivot = arr[high];
		i = low;
		j = low - 1;
		while (++j < high)
		{
			if (arr[j] < pivot)
			{
				temp = arr[i];
				arr[i++] = arr[j];
				arr[j] = temp;
			}
		}
		temp = arr[i];
		arr[i] = arr[high];
		arr[high] = temp;
		quicksort(arr, low, i - 1);
		quicksort(arr, i + 1, high);
	}
}
