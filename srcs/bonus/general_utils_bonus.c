/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 16:57:21 by craimond          #+#    #+#             */
/*   Updated: 2023/12/03 19:08:53 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

void	free_everything(t_stacks stacks, int *sorted_arr, char **argv)
{
	f_lstclear(stacks.sa);
	free(stacks.sa);
	free(stacks.sb);
	free(sorted_arr);
	free_matrix(argv);
}

char	scmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (1);
	return (0);
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
	if (*nptr != '\0' || n * sign > INT_MAX || n * sign < INT_MIN)
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
