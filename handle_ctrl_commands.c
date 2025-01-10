/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ctrl_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:00:05 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/09 14:33:28 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ctrl_c_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		rl_replace_line("", 0);
		write(STDOUT_FILENO, "\n", 1);
		write(STDOUT_FILENO, PROMPT, sizeof(PROMPT) - 1);
	}
}

void	ctrl_commands(char **line)
{
	struct sigaction	sa_ctrl_c;

	(void)line;
	sa_ctrl_c.sa_sigaction = ctrl_c_handler;
	sa_ctrl_c.sa_flags = SA_SIGINFO | SA_RESTART;
	sigemptyset(&sa_ctrl_c.sa_mask);
	sigaction(SIGINT, &sa_ctrl_c, NULL);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGUSR1, SIG_IGN);
}
