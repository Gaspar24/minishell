/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:51:28 by tlupu             #+#    #+#             */
/*   Updated: 2024/07/10 23:18:35 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #ifndef PARCING_H
// # define PARCING_H

// //  # include "minishell.h"

// typedef enum s_token_type
// {
// 	END,
// 	ERROR,
// 	PIPE,
// 	WORD,
// 	REDIRECT,
// 	QUOTE,
// 	REDIRECT_IN,     // <
// 	REDIRECT_OUT,    // >
// 	REDIRECT_APPEND, // >>  
// 	HEREDOC, // <<
// 	PIPE_PRES,
// 	NO_PIPPE_PRES  
// }						t_token_type;

// typedef struct s_list_token
// {
// 	t_token_type		type;
// 	int					index;
// 	char				*word;
// 	char				*token;
// 	char				**arr;
// 	struct s_list_token	*next;
// 	struct s_list_token	*prev;
// }						t_list_token;

// typedef struct s_word_info
// {
//     char    *word;
// 	t_token_type details;
//     int     char_counted;
// }           t_word_info;
// #endif

#ifndef PARCING_H
# define PARCING_H

//  # include "minishell.h"

typedef enum s_token_type
{
	END,
	ERROR,
	PIPE,
	WORD,
	REDIRECT,
	QUOTE,
	REDIRECT_IN, // <
	REDIRECT_OUT,// >
	REDIRECT_APPEND, // >>  
	HEREDOC, // <<
	PIPE_PRES,
	NO_PIPPE_PRES
}						t_token_type;

typedef struct s_list_token
{
	t_token_type		type;
	int					index;
	char				*word;
	char				*token;
	char				**arr;

	struct s_list_token	*next;
	struct s_list_token	*prev;
}						t_list_token;

typedef struct s_word_info
{
	char			*word;
	t_token_type	details;
	int				char_counted;
}			t_word_info;

typedef struct s_word_info_redirect
{
	char						**arr;
	t_token_type				token;
	struct s_word_info_redirect	*next;
}				t_word_info_redirect;

#endif