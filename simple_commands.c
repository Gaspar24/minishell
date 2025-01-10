/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 20:37:01 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/10 22:40:04 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_process(char *path, char **argv, t_env_var *vars)
{
	int	pid;
	int	status;

	status = 0;
	pid = fork();
	if (pid == 0)
	{
		if (execve(path, argv, vars->arr) == -1)
		{
			perror("execve");
			exit(127);
		}
	}
	else if (pid < 0)
		perror("fork");
	else
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			vars->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			vars->exit_status = WTERMSIG(status);
	}
}

int	count_tokens(t_list_token *data)
{
	int				count;
	t_list_token	*curr;

	count = 0;
	curr = data;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return (count);
}

char	**fill_argv(t_list_token *data, t_env_var *vars)
{
	int				i;
	t_list_token	*curr;
	char			**argv;

	i = count_tokens(data);
	argv = (char **)malloc(sizeof(char *) * (i + 1));
	curr = data;
	i = 0;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->word, "$?") == 0)
			argv[i++] = ft_itoa(vars->exit_status);
		else
			argv[i++] = ft_strdup(curr->word);
		curr = curr->next;
	}
	argv[i] = NULL;
	return (argv);
}

t_env_var	*check_path_fail(t_env_var *vars, char *path, char **argv)
{
	vars->flag_path = 0;
	if (!path)
	{
		printf("%s: command not found\n", argv[0]);
		free_exec_args(path, argv);
		vars->exit_status = 127;
		vars->flag_path = 1;
		return (vars);
	}
	return (vars);
}

t_env_var	*exec_line(t_list_token *data, t_env_var *vars)
{
	int		i;
	char	**argv;
	char	*path;

	argv = fill_argv(data, vars);
	if (check_if_builtin(argv[0]))
	{
		vars = handle_tokens_in_prompt(argv, &vars);
		i = 0;
		while (argv[i])
			free(argv[i++]);
		free(argv);
		return (vars);
	}
	path = get_path(argv[0], vars);
	if (!ft_strcmp(argv[0], "./minishell") || !ft_strcmp(argv[0], "minishell"))
		path = (ft_strdup("./minishell"));
	vars = check_path_fail(vars, path, argv);
	if (vars->flag_path)
		return (vars);
	execute_process(path, argv, vars);
	free_exec_args(path, argv);
	return (vars);
}
