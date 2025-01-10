/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_env_variables2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:56:35 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 22:40:04 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_vars(t_env_var *vars)
{
	int	i;

	i = 0;
	while (vars->arr[i])
	{
		free(vars->arr[i]);
		i++;
	}
	free(vars->arr);
	free(vars);
}

t_env_var	*init_and_copy_env_var(t_env_var *old_env_vars, int size)
{
	t_env_var	*new_env;
	int			i;

	new_env = malloc(sizeof(t_env_var));
	if (!new_env)
		return (NULL);
	new_env->arr = malloc(sizeof(char *) * (size + 2));
	if (!new_env->arr)
	{
		free(new_env);
		return (NULL);
	}
	i = 0;
	while (i < size)
	{
		new_env->arr[i] = old_env_vars->arr[i];
		i++;
	}
	new_env->arr[size] = NULL;
	return (new_env);
}

t_env_var	*add_env_var(t_env_var *old_env_vars, char *word)
{
	int			size;
	t_env_var	*new_env;

	size = 0;
	while (old_env_vars->arr[size])
		size++;
	new_env = init_and_copy_env_var(old_env_vars, size);
	if (!new_env)
		return (NULL);
	new_env->arr[size] = ft_strdup(word);
	if (!new_env->arr[size])
	{
		free_vars(new_env);
		return (NULL);
	}
	new_env->arr[size + 1] = NULL;
	free(old_env_vars->arr);
	free(old_env_vars);
	return (new_env);
}

// t_env_var	*add_env_var(t_env_var *old_env_vars, char *word)
// {
// 	int			i;
// 	int			j;
// 	t_env_var	*new_env;

// 	new_env = malloc(sizeof(t_env_var));
// 	if (!new_env)
// 		return (NULL);
// 	i = 0;
// 	while (old_env_vars->arr[i])
// 		i++;
// 	new_env->arr = malloc(sizeof(char *) * (i + 2));
// 	if (!new_env->arr)
// 	{
// 		free(new_env);
// 		return (NULL);
// 	}
// 	j = -1;
// 	while (++j < i)
// 		new_env->arr[j] = old_env_vars->arr[j];
// 	new_env->arr[j] = strdup(word);
// 	if (!new_env->arr[j])
// 	{
// 		free_vars(new_env);
// 		return (NULL);
// 	}
// 	new_env->arr[j + 1] = NULL;
// 	free(old_env_vars->arr);
// 	free(old_env_vars);
// 	return (new_env);
// }

char	**refill_arr(t_env_var *old_env_vars, t_env_var *new_env, char *key)
{
	int		i;
	char	*old_key;
	int		j;

	j = 0;
	i = -1;
	while (old_env_vars->arr[++i] != NULL)
	{
		old_key = get_key_from_word(old_env_vars->arr[i]);
		if (ft_strcmp(key, old_key) != 0)
		{
			new_env->arr[j] = old_env_vars->arr[i];
			j++;
		}
		else
			free(old_env_vars->arr[i]);
		free(old_key);
	}
	new_env->arr[j] = NULL;
	return (new_env->arr);
}

t_env_var	*delete_env_var(t_env_var *old_env_vars, char *key)
{
	int			i;
	int			j;
	t_env_var	*new_env;

	j = 0;
	new_env = malloc(sizeof(t_env_var));
	if (!new_env)
		return (NULL);
	i = 0;
	while (old_env_vars->arr[i])
		i++;
	new_env->arr = malloc(sizeof(char *) * i);
	if (!new_env->arr)
	{
		free(new_env);
		return (NULL);
	}
	new_env->arr = refill_arr(old_env_vars, new_env, key);
	free(old_env_vars->arr);
	free(old_env_vars);
	return (new_env);
}
