/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 18:26:26 by craimond          #+#    #+#             */
/*   Updated: 2023/12/03 19:33:59 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: craimond <craimond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 17:50:15 by craimond          #+#    #+#             */
/*   Updated: 2023/12/03 18:21:35 by craimond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

static char		**f_split(char *s, char c);
static int		count_words(char *s, char c);
static char		**fill_matrix(int n_words, char *s, char c, char **str_array);
static char		*ft_strdup(const char *s);
static size_t	ft_strlen(const char *c);
char			**free_matrix(char **str_array);

char	**handle_split(int *argc, char **argv)
{
	int 	i;
	char	**new_argv;
	
	i = -1;
	if (*argc == 2)
	{
		*argc = count_words(argv[1], ' ') + 1;
		return (f_split(argv[1], ' '));	
	}
	else
	{
		new_argv = malloc(sizeof(char *) * *argc);
		while (++i < *argc)
			new_argv[i] = ft_strdup(argv[i]);
		return (new_argv);
	}
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
	n_words = count_words(s, c);
	str_array = malloc(sizeof(char *) * (n_words + 1));
	if (!str_array)
		error(1);
	str_array[n_words] = NULL;
	return (fill_matrix(n_words, s, c, str_array));
}

static int	count_words(char *s, char c)
{
	int	 	n_words;
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

char	**free_matrix(char **str_array)
{
	int	g;

	g = -1;
	while (str_array[++g])
		free(str_array[g]);
	free(str_array);
	return (NULL);
}

static char	*ft_strdup(const char *s)
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

size_t	ft_strlen(const char *c)
{
	size_t	n;

	n = 0;
	while (c[n])
		n++;
	return (n);
}
