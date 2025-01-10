/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:13:02 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/11 16:00:36 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_path_fail_red(char *path, t_list_commands_red *cmd)
{
	if (!path)
	{
		printf("%s: command not found\n", cmd->arr[0]);
		free(path);
		_exit(127);
	}
}

void	execute_child_process(t_list_commands_red *cmd, t_env_var *vars)
{
	char				*path;
	t_list_commands_red	*current_cmd;
	t_list_commands_red	*last_cmd;

	current_cmd = cmd;
	last_cmd = NULL;
	while (current_cmd != NULL)
	{
		if ((ft_strcmp(current_cmd->red, ">") == 0
				|| ft_strcmp(current_cmd->red, ">>") == 0
				|| ft_strcmp(current_cmd->red, "<") == 0
				|| ft_strcmp(current_cmd->red, "<<") == 0))
			last_cmd = current_cmd;
		current_cmd = current_cmd->next;
	}
	fd_handeler(cmd, last_cmd);
	if (cmd->arr[0] == NULL)
		exit(127);
	path = get_path(cmd->arr[0], vars);
	check_path_fail_red(path, cmd);
	execve(path, cmd->arr, vars->arr);
	free(path);
	perror("execve");
	exit(127);
}

void	execute_command_red(t_list_commands_red *cmd, t_env_var *vars)
{
	int	status;
	int	pid;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		execute_child_process(cmd, vars);
	}
	else
	{
		waitpid(pid, &status, 0);
		unlink("temp_file");
		if (WIFEXITED(status))
			vars->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			vars->exit_status = WTERMSIG(status);
	}
}

t_list_commands_red	*initialize_new_cmd(void)
{
	t_list_commands_red	*new_cmd;

	new_cmd = malloc(sizeof(t_list_commands_red));
	if (!new_cmd)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	new_cmd->arr = NULL;
	new_cmd->red = NULL;
	new_cmd->file = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}
