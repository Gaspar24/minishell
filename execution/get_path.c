/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 11:52:15 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/11 15:55:44 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = (char *)malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1));
	if (!str)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

void	free_arr_path(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

char	*get_env_path(t_env_var *env_vars)
{
	int		i;
	char	*path;

	i = 0;
	while (env_vars->arr[i])
	{
		if (strncmp(env_vars->arr[i], "PATH=", 5) == 0)
		{
			path = env_vars->arr[i] + 5;
			return (path);
		}
		i++;
	}
	return (NULL);
}

char	*get_path(char *command, t_env_var *env_vars)
{
	char	*path;
	char	**paths;
	char	*tmp;
	char	*full_path;
	int		i;

	path = get_env_path(env_vars);
	if (!path)
		return (NULL);
	paths = ft_split(path, ':');
	i = -1;
	while (paths[++i])
	{
		tmp = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(tmp, command);
		free(tmp);
		if (access(full_path, F_OK) == 0)
		{
			free_arr_path(paths);
			return (full_path);
		}
		free(full_path);
	}
	free_arr_path(paths);
	return (NULL);
}
