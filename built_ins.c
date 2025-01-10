/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/19 16:21:50 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 23:16:41 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env_var	*mini_unset(char **commands, t_env_var *env_vars)
{
	int	i;

	if (commands[1] == NULL)
	{
		printf("unset: requires an argument\n");
		env_vars->exit_status = 1;
		return (env_vars);
	}
	i = 1;
	while (commands[i] != NULL)
	{
		if (ft_strchr(commands[i], '=') == NULL)
			env_vars = remove_env_var(commands[i], env_vars);
		i++;
	}
	env_vars->exit_status = 0;
	return (env_vars);
}

void	print_env_vars(char **commands, t_env_var *env_vars)
{
	int		i;
	char	*key_from_word;

	i = 0;
	if (commands[1] == NULL)
	{
		while ((env_vars)->arr[i] != NULL)
		{
			key_from_word = get_key_from_word((env_vars)->arr[i]);
			if (ft_strchr((env_vars)->arr[i], '=') == NULL)
				printf("declare -x %s\n", key_from_word);
			else
				printf("declare -x %s=\"%s\"\n", key_from_word,
					ft_strchr((env_vars)->arr[i], '=') + 1);
			free(key_from_word);
			i++;
		}
		(env_vars)->exit_status = 0;
	}
}

int	validate_command(char *command, t_env_var **env_vars)
{
	if (!check_if_alphanumeric(command))
	{
		printf("minishell: export: %s: not a valid identifier\n", command);
		(*env_vars)->exit_status = 1;
		return (0);
	}
	return (1);
}

void	handle_command_without_equal(char **command, t_ex *params)
{
	free(params->key);
	free(params->value);
	params->key = strdup(*command);
	params->value = strdup("");
}

void	handle_command_with_equal(char **command, t_ex *params)
{
	free(params->key);
	free(params->value);
	params->equal_pos = strchr(*command, '=');
	params->key_len = params->equal_pos - *command;
	params->key = malloc(params->key_len + 1);
	strncpy(params->key, *command, params->key_len);
	params->key[params->key_len] = '\0';
	params->value = strdup(params->equal_pos + 1);
}

// t_env_var	*mini_export(char **commands, t_env_var **env_vars)
// {
// 	int		i;
// 	char	*equal_pos;
// 	char	*key;
// 	char	*value;
// 	int		key_len;
// 	int		j;
// 	char 	*copy;

// 	print_env_vars(commands, *env_vars);
// 	i = 1;
// 	while (commands[i] != NULL)
// 	{
// 		if (!check_if_alphanumeric(commands[i]))
// 		{
// 			printf("minishell: export: %s: not a valid identifier\n",
// 				commands[i]);
// 			(*env_vars)->exit_status = 1;
// 			return (*env_vars);
// 		}
// 		equal_pos = ft_strchr(commands[i], '=');
// 		if (equal_pos == NULL)
// 		{
// 			key = ft_strdup(commands[i]);
// 			value = ft_strdup("");
// 		}
// 		else
// 		{
// 			key_len = equal_pos - commands[i];
// 			key = malloc(key_len + 1);
// 			strncpy(key, commands[i], key_len);
// 			key[key_len] = '\0';
// 			value = ft_strdup(equal_pos + 1);
// 		}
// 		j = 0;
// 		while ((*env_vars)->arr[j] != NULL)
// 		{
//             copy = get_key_from_word((*env_vars)->arr[j]);
//             if (ft_strcmp(key, copy) == 0)
//             {
//                 free(copy);
//                 free((*env_vars)->arr[j]);
//                 (*env_vars)->arr[j] = ft_strdup(commands[i]);
//                 free(key);
//                 free(value);
//                 return (*env_vars);
//             }
//             free(copy);
//             j++;
//         }
//         *env_vars = add_env_var(*env_vars, commands[i]);
//         free(key);
//         free(value);
//         i++;
//     }
//     (*env_vars)->exit_status = 0;
//     return (*env_vars);
// }
