/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:45:08 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/11 16:11:58 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_exit_status(t_env_var *vars)
{
	char	*status_str;

	status_str = ft_itoa(vars->exit_status);
	ft_putstr(status_str);
	ft_putstr(" ");
	free(status_str);
}

void	print_variable_value(char *command, t_env_var *vars)
{
	char	*value;

	value = get_value_from_var(command + 1, vars);
	if (value != NULL)
	{
		ft_putstr(value);
		ft_putstr(" ");
	}
}

void	process_command(char **commands, int i, t_env_var *vars)
{
	while (commands[i] != NULL)
	{
		if (commands[i][0] == '$')
		{
			if (ft_strcmp(commands[i], "$?") == 0)
			{
				print_exit_status(vars);
				vars->exit_status = 0;
			}
			else
				print_variable_value(commands[i], vars);
		}
		else
		{
			ft_putstr(commands[i]);
			ft_putstr(" ");
		}
		i++;
	}
}

int	handle_flags(char **commands, int *print_newline)
{
	int	i;
	int	j;

	i = 1;
	while (commands[i] != NULL && commands[i][0] == '-'
		&& commands[i][1] != '\0')
	{
		j = 1;
		while (commands[i][j] == 'n')
			j++;
		if (commands[i][j] == '\0')
		{
			*print_newline = 0;
			i++;
		}
		else
		{
			break ;
		}
	}
	return (i);
}

void	mini_echo(char **commands, t_env_var *vars)
{
	int	i;
	int	print_newline;

	print_newline = 1;
	if (commands[1] == NULL)
	{
		ft_putstr("\n");
		return ;
	}
	i = handle_flags(commands, &print_newline);
	process_command(commands, i, vars);
	if (print_newline)
		ft_putstr("\n");
	vars->exit_status = 0;
}
