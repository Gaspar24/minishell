/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   custom_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:17:27 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/10 23:16:05 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	words_count(const char *str, char c)
{
	t_info	p;

	init_info(&p);
	while (str[p.i] != '\0')
	{
		if (str[p.i] == '"' || str[p.i] == '\'')
		{
			update_word_flag1(&p, str);
			continue ;
		}
		if (!p.is_quote)
			update_word_flag2(&p, str, c);
		else if (!p.is_word_started)
			p.is_word_started = true;
		p.i++;
	}
	if (p.quotes % 2 != 0)
		return (printf("Error: Missing end quote\n"), -1);
	if (p.is_word_started)
		p.word++;
	return (p.word);
}

int	allocate_for_strings(const char *str, char c)
{
	int		i[2];
	bool	is_quote;

	i[0] = 0;
	i[1] = 0;
	is_quote = false;
	while (str[i[0]] != '\0')
	{
		if (str[i[0]] == '"' || str[i[0]] == '\'')
		{
			is_quote = !is_quote;
			i[1]++;
		}
		else if (!is_quote)
		{
			if (str[i[0]] != c)
				i[1]++;
		}
		else
			i[1]++;
		i[0]++;
	}
	return (i[1]);
}

// looks for the desired string keeping
// in mind all the special operators such as "",

// Main function to generate word info
t_word_info	string_gen(char *str, char c)
{
	t_dat		indexes;
	t_word_info	word_info;
	int			alloc;

	init_info_dat(&indexes);
	word_info.word = NULL;
	alloc = allocate_memory(str, c, &word_info);
	process_string(str, &indexes, &word_info, c);
	finalize_word_info(&indexes, &word_info);
	return (word_info);
}

char	**custom_split(const char *str, char c)
{
	int			i;
	int			index_array;
	char		**arr;
	int			word_length;
	t_word_info	word_info;

	i = 0;
	index_array = 0;
	word_length = words_count(str, c);
	if (word_length == -1)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (word_length + 1));
	if (!arr)
		return (printf("Error: Missing end quote\n"), NULL);
	while (index_array < word_length)
	{
		while (str[i] == c)
			i++;
		word_info = string_gen((char *)(str + i), c);
		arr[index_array] = word_info.word;
		i += word_info.char_counted;
		index_array++;
	}
	arr[word_length] = NULL;
	return (arr);
}
