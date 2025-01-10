/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 13:22:42 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 22:36:59 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_path_fail_pipe(char *path)
{
	if (!path)
	{
		printf("minishell : command not found\n");
		free(path);
		_exit(127);
	}
}

t_env_var	*builtin_check_in_pipe(t_list_commands *cmd, t_env_var *vars)
{
	vars->flag_mod = 0;
	if (check_if_builtin(cmd->arr[0]))
	{
		if (execute_builtins_with_no_output(cmd->arr, vars) == 1)
		{
			vars->flag_mod = 1;
			vars->num_cmds--;
		}
		else if (check_for_env_commands(cmd->arr))
		{
			vars->flag_mod = 1;
			vars->num_cmds--;
		}
	}
	return (vars);
}

void	child_process(t_list_commands *current,
int (*pipes)[2], t_env_var *vars, int i)
{
	char	*path;
	int		j;

	j = -1;
	if (i > 0)
		dup2(pipes[i - 1][0], STDIN_FILENO);
	if (i < vars->num_cmds - 1)
		dup2(pipes[i][1], STDOUT_FILENO);
	while (++j < vars->num_cmds - 1)
	{
		close(pipes[j][0]);
		close(pipes[j][1]);
	}
	if (check_if_builtin(current->arr[0]))
	{
		if (execute_builtins_with_output(current->arr, vars) == 1)
			_exit(EXIT_SUCCESS);
	}
	else
	{
		path = get_path(current->arr[0], vars);
		check_path_fail_pipe(path);
		execve(path, current->arr, vars->arr);
		perror("execve");
	}
}

t_env_var	*parent_process(t_list_commands *current, int pid,
		int (*pipes)[2], t_env_var *vars)
{
	int	status;
	int	i;

	i = vars->index;
	status = 0;
	if (i > 0)
		close(pipes[i - 1][0]);
	if (i < vars->num_cmds - 1)
		close(pipes[i][1]);
	if (ft_strcmp(current->arr[0], "cat") != 0)
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		vars->exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		vars->exit_status = WTERMSIG(status);
	return (vars);
}

t_env_var	*execute_commands(t_list_commands *current,
			int (*pipes)[2], t_env_var *vars)
{
	vars->i = 0;
	while (vars->i < vars->num_cmds)
	{
		vars = builtin_check_in_pipe(current, vars);
		if (vars->flag_mod == 1)
		{
			current = current->next;
			continue ;
		}
		vars->pid = fork();
		check_pid(vars, pipes);
		if (vars->pid == 0)
			child_process(current, pipes, vars, vars->i);
		else
		{
			vars->index = vars->i;
			vars = parent_process(current, vars->pid, pipes, vars);
		}
		current = current->next;
		vars->i++;
	}
	return (vars);
}
