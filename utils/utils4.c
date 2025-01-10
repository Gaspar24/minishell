/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 15:03:22 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/11 13:32:19 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list_token	*ft_lstlast(t_list_token *lst)
{
	t_list_token	*current;

	current = lst;
	while (current != NULL)
	{
		if (current->next == NULL)
			break ;
		current = current->next;
	}
	return (current);
}

char	*ft_strdup(char *s1)
{
	int		i;
	int		j;
	char	*s2;

	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		i++;
	}
	s2 = (char *)malloc((i + 1) * sizeof(char));
	if (s2 == NULL)
	{
		return (NULL);
	}
	while (j <= i)
	{
		s2[j] = s1[j];
		j++;
	}
	return (s2);
}

void	free_list(t_list_token *head)
{
	t_list_token	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		if (tmp->word)
			free(tmp->word);
		free(tmp);
	}
}

int	count_digits(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		return (1);
	if (n < 0)
		n = -n;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char		*number_str;
	int			d_count;
	int			i;
	long long	temp;

	d_count = count_digits(n);
	temp = n;
	i = d_count;
	number_str = (char *)malloc((d_count +1) * sizeof(char));
	if (!number_str)
		return (NULL);
	if (temp == 0)
		number_str[0] = '0';
	while (temp != 0)
	{
		if (temp < 0)
		{
			number_str[0] = '-';
			temp = -temp;
		}
		number_str[(i--) - 1] = (temp % 10) + '0';
		temp = temp / 10;
	}
	number_str[d_count] = '\0';
	return (number_str);
}
