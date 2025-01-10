/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:46:41 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 22:43:51 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//update env->$PWD -- need to do
int	mini_cd(char **commands, t_env_var *vars)
{
	(void)vars;
	if (commands[1] == NULL)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			perror("cd");
			vars->exit_status = 1;
			return (1);
		}
	}
	else
	{
		if (chdir(commands[1]) != 0)
		{
			perror("cd");
			return (1);
		}
	}
	return (0);
}

//getcwd --> get current directory
void	mini_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (cwd == NULL)
	{
		perror("pwd");
	}
	else
	{
		ft_putstr(cwd);
		ft_putstr("\n");
		free(cwd);
	}
}

void	mini_exit(char **commands, int last_exit_status)
{
	int	exit_status;

	exit_status = last_exit_status;
	if (commands[1] != NULL)
	{
		if (commands[2] != NULL)
		{
			ft_putstr("exit\nminishell: exit: too many arguments\n");
			return ;
		}
		exit_status = atoi(commands[1]);
	}
	ft_putstr("exit\n");
	exit(exit_status % 256);
}

void	mini_env(t_env_var *env_vars)
{
	int	i;

	i = 0;
	while (env_vars->arr[i])
	{
		if (ft_strchr(env_vars->arr[i], '=') != NULL)
		{
			ft_putstr(env_vars->arr[i]);
			ft_putstr("\n");
		}
		i++;
	}
}

// t_env_var	*mini_unset(char **commands, t_env_var *env_vars)
// {
// 	int		i;
// 	int		flag;
// 	char	*key;
// 	int		j;

// 	i = 0;
// 	if (commands[1] == NULL)
// 	{
// 		printf("unset: requires an argument\n");
// 		env_vars->exit_status = 1;
// 		return (env_vars);
// 	}
// 	while (commands[i] != NULL)
// 	{
// 		if (strchr(commands[i], '=') != NULL)
// 		{
// 			i++;
// 			continue ;
// 		}
// 		flag = 0;
// 		j = -1;
// 		while (env_vars->arr[++j] != NULL)
// 		{
// 			key = get_key_from_word(env_vars->arr[j]);
// 			if (strcmp(commands[i], key) == 0)
// 			{
// 				flag = 1;
// 				free(key);
// 				break ;
// 			}
// 			free(key);
// 		}
// 		if (flag == 1)
// 			env_vars = delete_env_var(env_vars, commands[i]);
// 		i++;
// 	}
// 	env_vars->exit_status = 0;
// 	return (env_vars);
// }
