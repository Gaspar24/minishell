/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_utils1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 18:56:40 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/10 23:15:17 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_info(t_info *p)
{
	p->i = 0;
	p->word = 0;
	p->quotes = 0;
	p->is_quote = false;
	p->is_word_started = false;
}

void	init_info_dat(t_dat *p)
{
	p->i = 0;
	p->word = 0;
	p->j = 0;
	p->is_quotes = false;
	p->is_word_started = false;
}

void	update_word_flag1(t_info *p, const char *str)
{
	p->is_quote = !p->is_quote;
	while (str[p->i] == '"' || str[p->i] == '\'')
	{
		p->i++;
		p->quotes++;
	}
	if (p->is_quote)
		p->is_word_started = true;
}

void	update_word_flag2(t_info *p, const char *str, char c)
{
	if ((p->i == 0 || str[p->i - 1] == c || str[p->i] == '|') && str[p->i] != c)
	{
		p->is_word_started = true;
		if (str[p->i] == '|' && str[p->i - 1] != c)
			p->word++;
	}
	if (str[p->i] == c || str[p->i] == '|')
	{
		if (p->is_word_started)
		{
			p->word++;
			p->is_word_started = false;
		}
		if (str[p->i] == '|' && str[p->i + 1] != '\0' && str[p->i + 1] != c
			&& str[p->i + 1] != '|')
			p->is_word_started = true;
	}
}
