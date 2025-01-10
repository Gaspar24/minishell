/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 23:00:17 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 23:13:34 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_ex(t_ex *param)
{
	param->i = 1;
	param->equal_pos = NULL;
	param->key = NULL;
	param->value = NULL;
	param->key_len = 0;
	param->j = 0;
	param->copy = NULL;
}

t_env_var	*update_or_add_env_var(t_env_var **env_vars, t_ex *params,
							char **commands)
{
	params->j = 0;
	while ((*env_vars)->arr[params->j] != NULL)
	{
		params->copy = get_key_from_word((*env_vars)->arr[params->j]);
		if (strcmp(params->key, params->copy) == 0)
		{
			free(params->copy);
			free((*env_vars)->arr[params->j]);
			(*env_vars)->arr[params->j] = strdup(*commands);
			return (*env_vars);
		}
		free(params->copy);
		params->j++;
	}
	*env_vars = add_env_var(*env_vars, *commands);
	return (*env_vars);
}

t_env_var	*mini_export(char **commands, t_env_var **env_vars)
{
	t_ex	params;

	print_env_vars(commands, *env_vars);
	init_ex(&params);
	while (commands[params.i] != NULL)
	{
		if (!validate_command(commands[params.i], env_vars))
		{
			free(params.key);
			free(params.value);
			return (*env_vars);
		}
		if (strchr(commands[params.i], '=') == NULL)
			handle_command_without_equal(&commands[params.i], &params);
		else
			handle_command_with_equal(&commands[params.i], &params);
		if (!update_or_add_env_var(env_vars, &params, &commands[params.i]))
			continue ;
		params.i++;
	}
	free(params.key);
	free(params.value);
	(*env_vars)->exit_status = 0;
	return (*env_vars);
}
