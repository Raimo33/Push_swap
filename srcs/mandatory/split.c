/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:50:15 by craimond          #+#    #+#             */
/*   Updated: 2023/12/04 14:17:57 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static char		**f_split(char *s, char c);
static int		count_words(char *s, char c);
static char		**fill_matrix(int n_words, char *s, char c, char **str_array);

char	**handle_split(int *argc, char **argv)
{
	int		i;
	char	**new_argv;

	i = -1;
	if (*argc == 2)
	{
		*argc = count_words(argv[1], ' ') + 1;
		new_argv = f_split(argv[1], ' ');
		if (!new_argv[0])
			error(2);
	}
	else
	{
		new_argv = malloc(sizeof(char *) * (*argc + 1));
		while (++i < *argc)
			new_argv[i] = ft_strdup(argv[i]);
		new_argv[i] = NULL;
	}
	return (new_argv);
}

static char	**f_split(char *s, char c)
{
	int		n_words;
	char	**str_array;

	if (!s || *s == '\0')
	{
		str_array = ft_calloc(sizeof(char *), 1);
		if (!str_array)
			error(1);
		return (str_array);
	}
	n_words = count_words(s, c) + 1;
	str_array = malloc(sizeof(char *) * (n_words + 1));
	if (!str_array)
		error(1);
	str_array[n_words] = NULL;
	return (fill_matrix(n_words, s, c, str_array));
}

static int	count_words(char *s, char c)
{
	int		n_words;
	short	i;

	i = -1;
	n_words = 0;
	if (s[0] != c && s[0] != '\0')
		n_words++;
	while (s[++i + 1] != '\0')
	{
		if (s[i] == c && s[i + 1] != c && s[i + 1] != '\0')
			n_words++;
	}
	return (n_words);
}

static char	**fill_matrix(int n_words, char *s, char c, char **str_array)
{
	int	g;
	int	i;
	int	len;

	g = -1;
	i = 0;
	len = 0;
	str_array[++g] = ft_strdup("./push_swap");
	while (++g < n_words)
	{
		while (*s == c)
			s++;
		while (s[len] != c && s[len] != '\0')
			len++;
		str_array[g] = malloc(sizeof(char) * (len + 1));
		if (!str_array[g])
			error(1);
		str_array[g][len++] = '\0';
		i = len - 1;
		while (--len > 0)
			str_array[g][len - 1] = s[len - 1];
		s += i;
	}
	return (str_array);
}
