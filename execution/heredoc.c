/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 15:20:05 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 22:36:59 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	input_file_from_temp(void)
{
	int	fd_in;

	fd_in = open("temp_file", O_RDONLY);
	if (fd_in < 0)
	{
		perror("open temp_file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		perror("dup2 temp_file");
		exit(EXIT_FAILURE);
	}
	close(fd_in);
}

void	handle_heredoc(char *delimiter)
{
	int		temp_fd;
	char	*buff;

	temp_fd = open("temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (temp_fd == -1)
	{
		perror("open temp_file");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		buff = readline("heredoc> ");
		if (!buff)
			break ;
		if (ft_strcmp(buff, delimiter) == 0)
		{
			free(buff);
			break ;
		}
		write(temp_fd, buff, strlen(buff));
		write(temp_fd, "\n", 1);
		free(buff);
	}
	close(temp_fd);
}

void	fd_handeler(t_list_commands_red *current_cmd,
		t_list_commands_red *last_cmd)
{
	while (current_cmd != NULL)
	{
		if (ft_strcmp(current_cmd->red, "<") == 0)
			input_file(current_cmd->file);
		else if (ft_strcmp(current_cmd->red, "<<") == 0)
		{
			handle_heredoc(current_cmd->file);
			input_file_from_temp();
		}
		else if ((ft_strcmp(current_cmd->red, ">") == 0
				|| ft_strcmp(current_cmd->red, ">>") == 0)
			&& current_cmd == last_cmd)
		{
			output_file(current_cmd->red, current_cmd->file, 1);
		}
		else if ((ft_strcmp(current_cmd->red, ">") == 0
				|| ft_strcmp(current_cmd->red, ">>") == 0)
			&& current_cmd != last_cmd)
		{
			output_file(current_cmd->red, current_cmd->file, 0);
		}
		current_cmd = current_cmd->next;
	}
}
