/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:00:41 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 22:40:04 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_nb_of_pipes(t_list_token *data)
{
	int				nb;
	t_list_token	*curr;

	nb = 0;
	curr = data;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->word, "|") == 0)
			nb++;
		curr = curr->next;
	}
	return (nb);
}

char	**fill_argv_array_pipe(t_list_token *data, char **argv, int count)
{
	t_list_token	*current;
	int				i;

	current = data;
	i = 0;
	while (i < count)
	{
		if (ft_strcmp(current->word, "|") == 0)
			break ;
		argv[i] = ft_strdup(current->word);
		if (argv[i] == NULL)
		{
			perror("strdup");
			exit(EXIT_FAILURE);
		}
		current = current->next;
		i++;
	}
	argv[count] = NULL;
	return (argv);
}

char	**convert_tokens_to_argv(t_list_token *data)
{
	int				count;
	t_list_token	*current;
	char			**argv;

	count = 0;
	current = data;
	while (current != NULL && ft_strcmp(current->word, "|") != 0)
	{
		count++;
		current = current->next;
	}
	argv = malloc((count + 1) * sizeof(char *));
	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	argv = fill_argv_array_pipe(data, argv, count);
	return (argv);
}

int	count_commands(t_list_commands *cmd)
{
	int				num_cmds;
	t_list_commands	*current;

	num_cmds = 0;
	current = cmd;
	while (current != NULL)
	{
		num_cmds++;
		current = current->next;
	}
	return (num_cmds);
}

void	cleanup_pipes_and_wait(int (*pipes)[2], int num_cmds)
{
	int	j;

	j = 0;
	while (j < num_cmds - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
		j++;
	}
	j = 0;
	while (j < num_cmds)
	{
		wait(NULL);
		j++;
	}
	free(pipes);
}
