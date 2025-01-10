/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirects.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 14:36:21 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 22:36:59 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	handle_redirection(t_list_commands_red *new_cmd, t_list_token **current)
{
	if (*current && (ft_strcmp((*current)->word, "<") == 0
			|| ft_strcmp((*current)->word, ">") == 0
			|| ft_strcmp((*current)->word, "<<") == 0
			|| ft_strcmp((*current)->word, ">>") == 0))
	{
		new_cmd->red = (*current)->word;
		if ((*current)->next)
		{
			new_cmd->file = (*current)->next->word;
			*current = (*current)->next->next;
		}
		else
		{
			new_cmd->file = NULL;
			*current = (*current)->next;
		}
	}
	else
		*current = NULL;
}

t_list_commands_red	*create_new_cmd(t_list_token **current)
{
	t_list_commands_red	*new_cmd;

	new_cmd = initialize_new_cmd();
	new_cmd->arr = convert_tokens_to_argv_red(*current);
	while (*current && ft_strcmp((*current)->word, "<") != 0
		&& ft_strcmp((*current)->word, ">") != 0
		&& ft_strcmp((*current)->word, "<<") != 0
		&& ft_strcmp((*current)->word, ">>") != 0)
		*current = (*current)->next;
	handle_redirection(new_cmd, current);
	return (new_cmd);
}

t_list_commands_red	*build_command_list(t_list_token *data)
{
	t_list_commands_red	*cmd_head;
	t_list_commands_red	*cmd_tail;
	t_list_token		*current;
	t_list_commands_red	*new_cmd;

	cmd_head = NULL;
	cmd_tail = NULL;
	current = data;
	while (current && ft_strcmp(current->word, "|") != 0)
	{
		new_cmd = create_new_cmd(&current);
		if (!cmd_head)
		{
			cmd_head = new_cmd;
			cmd_tail = new_cmd;
		}
		else
		{
			cmd_tail->next = new_cmd;
			cmd_tail = new_cmd;
		}
	}
	return (cmd_head);
}

void	execute_and_free_commands(t_list_commands_red *cmd_head,
			t_env_var *vars)
{
	t_list_commands_red	*cmd_curr;
	t_list_commands_red	*temp;

	cmd_curr = cmd_head;
	while (cmd_curr)
	{
		execute_command_red(cmd_curr, vars);
		cmd_curr = cmd_curr->next;
	}
	cmd_curr = cmd_head;
	while (cmd_curr)
	{
		temp = cmd_curr;
		cmd_curr = cmd_curr->next;
		free(temp->arr);
		free(temp);
	}
}

void	handle_redirects(t_list_token *data, t_env_var *vars)
{
	t_list_commands_red	*cmd_head;

	cmd_head = build_command_list(data);
	execute_and_free_commands(cmd_head, vars);
}
