/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 14:34:38 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 22:36:59 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	create_pipes(int (*pipes)[2], int num_cmds)
{
	int	i;

	i = 0;
	while (i < num_cmds - 1)
	{
		if (pipe(pipes[i]) == -1)
		{
			perror("pipe");
			free(pipes);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

int	(*allocate_pipes(int num_cmds))[2]
{
	int	(*pipes)[2];

	if (num_cmds < 2)
		return (NULL);
	pipes = malloc (sizeof(int [2]) * (num_cmds - 1));
	if (pipes == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	return (pipes);
}

t_env_var	*implementing_pipe(t_list_commands *cmd,
	t_env_var *env_vars, t_list_token *data)
{
	int	(*pipes)[2];

	env_vars->num_cmds = count_commands(cmd);
	(void) data;
	if (env_vars->num_cmds < 1)
		return (env_vars);
	pipes = allocate_pipes(env_vars->num_cmds);
	if (pipes != NULL)
		create_pipes(pipes, env_vars->num_cmds);
	env_vars = execute_commands(cmd, pipes, env_vars);
	if (pipes != NULL)
		cleanup_pipes_and_wait(pipes, env_vars->num_cmds);
	return (env_vars);
}

t_list_token	*move_node(t_list_token *current)
{
	while (current != NULL && ft_strcmp(current->word, "|") != 0)
		current = current->next;
	if (current != NULL && ft_strcmp(current->word, "|") == 0)
		current = current->next;
	return (current);
}

// maybe need to initialize with null;
t_env_var	*handle_pipe(t_list_token *data, t_env_var *env_vars)
{
	t_list_commands	*cmd_head;
	t_list_commands	*cmd_tail;
	t_list_token	*current;
	t_list_commands	*new_cmd;

	cmd_head = NULL;
	current = data;
	while (current != NULL)
	{
		new_cmd = handle_malloc_fail(new_cmd, current);
		if (cmd_head == NULL)
		{
			cmd_head = new_cmd;
			cmd_tail = new_cmd;
		}
		else
		{
			cmd_tail->next = new_cmd;
			cmd_tail = new_cmd;
		}
		current = move_node(current);
	}
	env_vars = implementing_pipe(cmd_head, env_vars, data);
	free_command_list(cmd_head);
	return (env_vars);
}
