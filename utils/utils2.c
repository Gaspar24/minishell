/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:50:53 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/10 23:13:44 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

t_list_token	*ft_lstnew_init(void)
{
	t_list_token	*new;

	new = NULL;
	new = (t_list_token *)malloc(sizeof(t_list_token));
	if (!new)
		return (NULL);
	return (new);
}

void	free_nodes(t_list_token *head)
{
	t_list_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		ft_lstreset(tmp, WORD);
		free(tmp);
		tmp = NULL;
	}
}

void	ft_lstreset(t_list_token *data, t_token_type token)
{
	if (data == NULL)
	{
		printf("Data is NULL\n");
		return ;
	}
	else if (data->word != NULL)
	{
		free(data->word);
		data->word = NULL;
	}
	data->index = 0;
	data->type = 0;
	if (token == END)
		data->word = NULL;
}

char	**turn_word_into_arr(t_list_token *data)
{
	int				i;
	char			**arr;
	t_list_token	*curr;

	i = 0;
	curr = data->next;
	while (curr != NULL)
	{
		i++;
		curr = curr->next;
	}
	arr = malloc((i + 1) * sizeof(char *));
	if (arr == NULL)
		return (0);
	curr = data;
	i = 0;
	while (curr != NULL)
	{
		arr[i++] = ft_strdup(curr->word);
		curr = curr->next;
	}
	arr[i] = NULL;
	return (arr);
}
