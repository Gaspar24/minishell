/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:50:59 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/10 22:45:15 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strdnup(const char *s1, int n)
{
	char	*str;
	int		i;

	str = (char *)malloc(sizeof(char) * (n + 2));
	if (!str)
		return (NULL);
	i = 0;
	while (i < n + 1 && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

void	free_token_list(t_list_token **stack)
{
	t_list_token	*tmp;
	t_list_token	*current;

	if (!stack)
		return ;
	current = *stack;
	while (current)
	{
		tmp = current->next;
		current->type = 0;
		current->index = 0;
		current->word = NULL;
		free(current);
		current = tmp;
	}
	*stack = NULL;
}

void	ft_lstadd_back(t_list_token **lst, t_list_token *new)
{
	t_list_token	*last;

	if (*lst == NULL)
	{
		*lst = new;
		return ;
	}
	last = *lst;
	while (last->next != NULL)
	{
		last = last->next;
	}
	last->next = new;
	new->prev = last;
}

t_list_token	*ft_lstnew(char *content, t_token_type token)
{
	t_list_token	*new;

	new = NULL;
	new = (t_list_token *)malloc(sizeof(t_list_token));
	if (!new)
		return (NULL);
	new->index = 0;
	new->type = 0;
	new->word = NULL;
	new->prev = NULL;
	if (token == QUOTE || token == WORD || token == REDIRECT || token == PIPE)
	{
		new->word = ft_strdup(content);
		new->type = token;
	}
	else
		printf("UNEXPECTED TOKEN TYPE\n");
	new->next = NULL;
	return (new);
}

bool	is_space(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\r'
		|| line[i] == '\v' || line[i] == '\f' || line[i] == '\n')
	{
		i++;
		if (line[i] == '\0')
			return (true);
	}
	return (false);
}
