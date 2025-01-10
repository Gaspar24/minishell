/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 19:19:12 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/11 14:44:03 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_exec_args(char *path, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		free(argv[i++]);
	free(argv);
	free (path);
}

t_env_var	*remove_env_var(char *command, t_env_var *env_vars)
{
	int		flag;
	char	*key;
	int		j;

	flag = 0;
	j = -1;
	while (env_vars->arr[++j] != NULL)
	{
		key = get_key_from_word(env_vars->arr[j]);
		if (ft_strcmp(command, key) == 0)
		{
			flag = 1;
			free(key);
			break ;
		}
		free(key);
	}
	if (flag == 1)
		env_vars = delete_env_var(env_vars, command);
	return (env_vars);
}

void	ft_putstr(char *str)
{
	write (1, str, strlen(str));
}

int	ft_strcmp(char *s1, char *s2)
{
	if (!s1 || !s2)
	{
		if (s1 == s2)
			return (0);
		if (s1)
			return (1);
		return (-1);
	}
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(unsigned char *)s1 - *(unsigned char *)s2);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = b;
	while (len > 0)
	{
		*ptr = c;
		ptr++;
		len--;
	}
	return (b);
}

// char	*ft_strchr(char *s, int c)
// {
// 	int	i;

// 	i = 0;
// 	c = c % 256;
// 	while (s[i] != '\0')
// 	{
// 		if (s[i] == c)
// 			return ((char *) s + i);
// 		i++;
// 	}
// 	if (c == '\0')
// 		return ((char *) s + i);
// 	return (NULL);
// }
