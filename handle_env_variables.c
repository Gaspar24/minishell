/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 18:06:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 22:43:51 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	check_if_alphanumeric(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!isalnum((unsigned char)str[i]) && str[i] != '=')
			return (false);
		i++;
	}
	return (true);
}

char	*get_value_from_var(char *word, t_env_var *vars)
{
	int		i;
	char	*key_from_word;

	i = 0;
	while (vars->arr[i])
	{
		key_from_word = get_key_from_word(vars->arr[i]);
		if (ft_strcmp(word, key_from_word) == 0)
		{
			free(key_from_word);
			return (ft_strchr(vars->arr[i], '=') + 1);
		}
		free(key_from_word);
		i++;
	}
	return (NULL);
}

char	*get_key_from_word(char *word)
{
	int		i;
	char	*key;

	i = 0;
	while (word[i] != '=' && word[i] != '\0')
	{
		i++;
	}
	key = malloc(i + 1);
	if (key == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	strncpy(key, word, i);
	key[i] = '\0';
	return (key);
}

/** !create 3 additional vars 
		 *  PWD=/home/msacaliu/42_projects/github_repos/minishell
		 *  SHLVL=1
		 *  _=/usr/bin/env
		 * */
t_env_var	*get_env_vars(char **envp)
{
	int			i;
	t_env_var	*vars;

	vars = malloc(sizeof(t_env_var));
	if (!vars)
	{
		return (NULL);
	}
	i = 0;
	while (envp[i])
		i++;
	vars->arr = malloc(sizeof(char *) * (i + 1));
	if (!vars->arr)
	{
		free(vars);
		return (NULL);
	}
	i = -1;
	while (envp[++i])
		vars->arr[i] = ft_strdup(envp[i]);
	vars->arr[i] = NULL;
	vars->exit_status = 0;
	return (vars);
}

bool	check_word(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '=')
	{
		if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z')
			|| (str[i] >= '0' && str[i] <= '9'))
			i++;
		else
			return (false);
	}
	return (true);
}
