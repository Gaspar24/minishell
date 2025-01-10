/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_for_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 11:28:53 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 15:42:56 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**free_arr_split(char **arr )

{
	int	i;

	i = 0;
	if (arr == NULL)
		return (NULL);
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

int	str_len_mod(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
	{
		i++;
	}
	return (i);
}

int	count_words(const char *str, char c)
{
	int	i;
	int	trigger;

	i = 0;
	trigger = 0;
	while (*str)
	{
		if (*str != c && trigger == 0)
		{
			trigger = 1;
			i++;
		}
		else if (*str == c)
		{
			trigger = 0;
		}
		str++;
	}
	return (i);
}

char	*create_word(const char *str, int start, char c)
{
	char	*word;
	int		i;

	i = 0;
	word = malloc((str_len_mod(&str[start], c) + 1) * sizeof(char));
	if (!word)
		return (NULL);
	while (str[start] != c && str[start] != '\0')
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	j;
	char	**arr;

	i = 0;
	j = 0;
	arr = malloc ((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !arr)
		return (free_arr_split(arr));
	while (s[i] != '\0')
	{
		if (s[i] == c)
			i++;
		else if ((s[i] != c))
		{
			arr[j] = create_word(s, i, c);
			if (!arr[j])
				return (free_arr_split(arr));
			j++;
			i = i + str_len_mod(&s[i], c);
		}
	}
	arr[j] = NULL;
	return (arr);
}
