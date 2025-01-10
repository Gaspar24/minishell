/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 13:30:42 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/09 13:30:43 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

//CVb3d2023
//
//void update_env_pwd(env_var *vars)
//{
//	char *cwd;
//	int i;
//	char *key;
//	char *new_path;
//
//	i = 0;
//	cwd = getcwd(NULL, 0);
//	if (cwd == NULL)
//	{
//		perror("pwd");
//		return ;
//	}
//	new_pwd = malloc(strlen("PWD=") + strlen(cwd) + 1);
//	if (new_pwd == NULL) {
//		perror("malloc");
//		free(cwd);
//		return;
//	}
//	(void)new_path;
//	while (vars->arr[i] != NULL)
//	{
//		key = get_key_from_word(vars->arr[i]);
//		if(strcmp("PWD", key) == 0)
//			add_env_var(vars, )
//		i++;
//	}
//	free(cwd);
//}
