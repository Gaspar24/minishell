/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_line_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:27:49 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 23:28:30 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_segment_redirect(t_list_token *segment_start,
		t_env_var *vars, bool *found_redirect)
{
	if (*found_redirect)
	{
		handle_redirects(segment_start, vars);
		*found_redirect = false;
	}
}

void	process_redirects(t_list_token *data, t_env_var *vars)
{
	t_list_token	*current;
	t_list_token	*segment_start;
	bool			found_redirect;

	current = data;
	segment_start = data;
	found_redirect = false;
	while (current != NULL)
	{
		if (ft_strcmp(current->word, ">") == 0
			|| ft_strcmp(current->word, "<") == 0
			|| ft_strcmp(current->word, ">>") == 0
			|| ft_strcmp(current->word, "<<") == 0)
			found_redirect = true;
		if (current->next == NULL || ft_strcmp(current->word, "|") == 0)
		{
			handle_segment_redirect(segment_start, vars, &found_redirect);
			segment_start = current->next;
		}
		current = current->next;
	}
}

void	process_pipes(t_list_token *data, t_env_var *vars)
{
	t_list_token	*current;
	t_list_token	*segment_start;
	bool			processed_segment;

	current = data;
	segment_start = data;
	processed_segment = false;
	while (current != NULL)
	{
		if (current->next != NULL
			&& ft_strcmp(current->word, "|") == 0 && !processed_segment)
		{
			vars = handle_pipe(segment_start, vars);
			processed_segment = true;
		}
		current = current->next;
	}
}

void	handle_pipe_and_red(t_list_token *data, t_env_var *vars)
{
	process_redirects(data, vars);
	process_pipes(data, vars);
}
