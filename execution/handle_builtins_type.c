/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_builtins_type.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 12:35:10 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 22:36:59 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	check_for_env_commands(char **commands)
{
	if (ft_strcmp(commands[0], "unset") == 0)
		return (true);
	if ((ft_strcmp(commands[0], "export") == 0) && commands[1] != NULL)
	{
		return (true);
	}
	else
		return (false);
}

int	execute_builtins_with_no_output(char **commands, t_env_var *vars)
{
	int	flag;

	flag = 0;
	if (ft_strcmp(commands[0], "cd") == 0)
	{
		mini_cd(commands, vars);
		flag++;
	}
	if (ft_strcmp(commands[0], "exit") == 0)
	{
		mini_exit(commands, vars->exit_status);
		flag++;
	}
	return (flag);
}

int	execute_builtins_with_output(char **commands, t_env_var *vars)
{
	int	flag;

	flag = 0;
	if (ft_strcmp(commands[0], "env") == 0)
	{
		mini_env(vars);
		flag = 1;
	}
	else if (ft_strcmp(commands[0], "echo") == 0)
	{
		mini_echo(commands, vars);
		flag = 1;
	}
	else if (ft_strcmp(commands[0], "pwd") == 0)
	{
		mini_pwd();
		flag = 1;
	}
	if ((ft_strcmp(commands[0], "export") == 0) && commands[1] == NULL)
	{
		mini_export(commands, &vars);
		flag = 1;
	}
	return (flag);
}

t_env_var	*exec_env_var_fct(char **commands, t_env_var *vars)
{
	t_env_var	*env_vars;

	env_vars = vars;
	if (ft_strcmp(commands[0], "unset") == 0)
	{
		env_vars = mini_unset(commands, vars);
	}
	if (ft_strcmp(commands[0], "export") == 0)
	{
		env_vars = mini_export(commands, &vars);
	}
	return (env_vars);
}
