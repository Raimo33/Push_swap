/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 19:40:25 by craimond          #+#    #+#             */
/*   Updated: 2023/12/04 14:19:33 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static size_t	ft_strlen(const char *c);

char	*ft_strdup(char *s)
{
	char	*new_str;
	short	i;

	i = -1;
	new_str = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!new_str)
		return (NULL);
	while (s[++i] != '\0')
		new_str[i] = s[i];
	return (new_str);
}

void	free_matrix(char **matrix)
{
	int	g;

	g = -1;
	while (matrix[++g])
		free(matrix[g]);
	free(matrix);
}

static size_t	ft_strlen(const char *c)
{
	size_t	n;

	n = 0;
	while (c[n])
		n++;
	return (n);
}
