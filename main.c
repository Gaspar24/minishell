/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:37:18 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 16:09:24 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "errno.h"

void	check_nb_of_args(int argc)
{
	if (argc != 1)
	{
		printf("Args are not allowed\n");
		exit(1);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_input			input;
	t_list_token	*data;
	t_env_var		*env_vars;

	(void)argv;
	check_nb_of_args(argc);
	input.prompt = PROMPT;
	env_vars = get_env_vars(envp);
	data = NULL;
	while (1)
	{
		ctrl_commands(&input.line);
		input.line = readline(input.prompt);
		if (input.line == NULL)
		{
			printf("exit\n");
			exit(1);
		}
		handle_line(&input, data, &env_vars);
		if (input.line && *input.line)
			add_history(input.line);
		free(input.line);
	}
	return (0);
}
