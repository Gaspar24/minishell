/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 11:50:33 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 23:14:27 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_if_builtin(char *word)
{
	int		num_of_builtins;
	char	*arr_of_builtins[7];
	int		i;

	i = 0;
	arr_of_builtins[0] = "echo";
	arr_of_builtins[1] = "cd";
	arr_of_builtins[2] = "export";
	arr_of_builtins[3] = "unset";
	arr_of_builtins[4] = "env";
	arr_of_builtins[5] = "exit";
	arr_of_builtins[6] = "pwd";
	num_of_builtins = sizeof(arr_of_builtins) / sizeof(arr_of_builtins[0]);
	while (i < num_of_builtins)
	{
		if (ft_strcmp(word, arr_of_builtins[i]) == 0)
		{
			return (true);
		}
		i++;
	}
	return (false);
}

bool	check_for_pipe_in_line(t_list_token *data)
{
	int				nb_of_pipes;
	t_list_token	*curr;
	bool			is_first;
	bool			last_was_pipe;

	nb_of_pipes = 0;
	curr = data;
	is_first = true;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->word, "|") == 0)
		{
			nb_of_pipes++;
			if (is_first || last_was_pipe)
				return (false);
			last_was_pipe = true;
		}
		else
			last_was_pipe = false;
		is_first = false;
		curr = curr->next;
	}
	if (last_was_pipe || nb_of_pipes == 0)
		return (false);
	return (true);
}

bool	check_for_redirects_in_line(t_list_token *data)
{
	bool			is_first;
	bool			last_was_redirect;
	int				nb_of_redirects;

	is_first = true;
	nb_of_redirects = 0;
	while (data != NULL)
	{
		if (ft_strcmp(data->word, ">") == 0 || ft_strcmp(data->word, ">>") == 0
			|| ft_strcmp(data->word, "<") == 0
			|| ft_strcmp(data->word, "<<") == 0)
		{
			nb_of_redirects++;
			if (is_first || last_was_redirect)
				return (false);
			last_was_redirect = true;
		}
		else
			last_was_redirect = false;
		is_first = false;
		data = data->next;
	}
	if (last_was_redirect || nb_of_redirects == 0)
		return (false);
	return (true);
}

void	check_pid(t_env_var *vars, int (*pipes)[2])
{
	if (vars->pid < 0)
	{
		perror("fork");
		free(pipes);
		exit(EXIT_FAILURE);
	}
}
;