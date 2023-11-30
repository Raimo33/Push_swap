/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:57:21 by craimond          #+#    #+#             */
/*   Updated: 2023/11/30 18:33:54 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	free_everything(char id, t_stacks stacks, int *sorted_arr)
{
	free(stacks.sa);
	free(stacks.sb);
	free(sorted_arr);
	if (id != 0)
		error(id);
}

char	f_strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

long	f_atol(char *nptr)
{
	long	n;
	char	sign;

	n = 0;
	sign = 1;
	while (*nptr == 32 || (*nptr >= '\t' && *nptr <= '\r'))
		nptr++;
	if (*nptr == '-')
	{
		sign = -1;
		nptr++;
	}
	else if (*nptr == '+')
		nptr++;
	if (*nptr > '9' || *nptr < '0')
		error(2);
	while (*nptr <= '9' && *nptr >= '0')
	{
		n *= 10;
		n += (*nptr - 48);
		nptr++;
	}
	if (n * sign > INT_MAX || n * sign < INT_MIN)
		error(2);
	return (n * sign);
}

void	error(char id)
{
	write(2, "Error\n", 6);
	exit(id);
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
