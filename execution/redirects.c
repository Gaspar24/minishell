/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirects.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 15:17:35 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/10 23:14:52 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	count_redirects(t_list_token *data)
{
	int				count;
	t_list_token	*curr;

	count = 0;
	curr = data;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->word, "<") == 0 || ft_strcmp(curr->word, ">") == 0
			|| ft_strcmp(curr->word, "<<") == 0
			|| ft_strcmp(curr->word, ">>") == 0)
			count++;
		curr = curr->next;
	}
	return (count);
}

char	**fill_argv_red(char **argv, t_list_token *curr, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		argv[i++] = curr->word;
		curr = curr->next;
	}
	argv[count] = NULL;
	return (argv);
}

char	**convert_tokens_to_argv_red(t_list_token *curr)
{
	int				count;
	t_list_token	*temp;
	char			**argv;

	temp = curr;
	count = 0;
	while (temp != NULL && ft_strcmp(temp->word, "<") != 0
		&& ft_strcmp(temp->word, ">") != 0
		&& ft_strcmp(temp->word, "<<") != 0 && ft_strcmp(temp->word, ">>") != 0)
	{
		count++;
		temp = temp->next;
	}
	argv = malloc((count + 1) * sizeof(char *));
	if (argv == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	argv = fill_argv_red(argv, curr, count);
	return (argv);
}

void	input_file(char *input_file)
{
	int	fd_in;

	fd_in = open(input_file, O_RDONLY);
	if (fd_in < 0)
	{
		perror("open input file");
		exit(EXIT_FAILURE);
	}
	if (dup2(fd_in, STDIN_FILENO) < 0)
	{
		perror("dup2 input file");
		exit(EXIT_FAILURE);
	}
	close(fd_in);
}

void	output_file(char *red, char *output_file, int is_last)
{
	int	fd_out;
	int	flags;

	flags = O_WRONLY | O_CREAT | O_TRUNC;
	if (is_last)
	{
		flags = O_WRONLY | O_CREAT;
		if (ft_strcmp(red, ">>") == 0)
			flags = O_WRONLY | O_CREAT | O_APPEND;
	}
	if (ft_strcmp(red, ">>") == 0 || ft_strcmp(red, ">") == 0)
	{
		fd_out = open(output_file, flags, 0644);
		if (fd_out < 0)
		{
			perror("open output file");
			exit(EXIT_FAILURE);
		}
		if (dup2(fd_out, STDOUT_FILENO) < 0)
		{
			perror("dup2 output file");
			exit(EXIT_FAILURE);
		}
		close(fd_out);
	}
}
