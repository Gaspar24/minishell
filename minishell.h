/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msacaliu <msacaliu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 17:18:10 by msacaliu          #+#    #+#             */
/*   Updated: 2024/07/11 14:43:14 by msacaliu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "parcing.h"
# include <dirent.h>
# include <fcntl.h>
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>

# define PROMPT "\033[1m\033[31mminihell*$> \033[0;34m"

typedef struct s_env_var
{
	char		**arr;
	int			exit_status;
	int			num_cmds;
	int			flag_mod;
	int			index;
	int			*exported;
	int			flag_path;
	int			pid; //just because norminettel
	int			i; // norminette shit
}	t_env_var;

typedef struct s_input
{
	char		*prompt;
	char		*line;
	char		*direct;
	int			quote_open;
}				t_input;

typedef struct s_list_commands
{
	char					**arr;
	char					*input_file;
	char					*output_file;
	int						append;
	struct s_list_commands	*next;
}							t_list_commands;
typedef struct s_list_commands_red
{
	char						**arr;
	char						*red;
	char						*file;
	struct s_list_commands_red	*next;
}								t_list_commands_red;

typedef struct s_info
{
	int							i;
	int							word;
	int							quotes;
	bool						is_quote;
	bool						is_word_started;
}								t_info;

typedef struct s_dat
{
	int							i;
	int							word;
	int							alloc;
	int							j;
	bool						is_quotes;
	bool						is_word_started;
}								t_dat;

typedef struct s_ex
{
	int							i;
	char						*equal_pos;
	char						*key;
	char						*value;
	int							key_len;
	int							j;
	char						*copy;
}								t_ex;
// utils
t_list_token		*ft_lstnew(char *content, t_token_type token);
void				ft_lstadd_back(t_list_token **lst, t_list_token *new);
void				free_token_list(t_list_token **stack);
char				*ft_strdnup(const char *s1, int n);
bool				is_space(char *line);

// builtins_new
void				handle_command_with_equal(char **command, t_ex *params);
void				handle_command_without_equal(char **command, t_ex *params);
int					validate_command(char *command, t_env_var **env_vars);
void				print_env_vars(char **commands, t_env_var *env_vars);
void				init_ex(t_ex *param);
// utils2

t_list_token		*ft_lstnew_init(void);
void				ft_lstreset(t_list_token *data, t_token_type token);
int					ft_strlen(const char *str);
void				free_nodes(t_list_token *head);
char				*ft_strrchr(const char *s, int c);
void				free_list(t_list_token *head);

// utils3
char				*ft_strchr(char *s, int c);
char				*ft_strdnnup(const char *s1, int n);
void				free_arr(char **arr);
void				ft_lstrest(t_list_token *data, t_token_type token);
char				**ft_split(const char *s, char c);

//-----------utils4

t_list_token		*ft_lstlast(t_list_token *lst);
char				*ft_strdup(char *s1);
void				print_node(t_list_token *node);
void				ft_putstr(char *str);
char				*ft_itoa(int n);

		/// ------------handle ctrl_commands--------------
void				ctrl_commands(char **line);

		// --------------handle line_input--------------
void				handle_line(t_input *input, t_list_token *data,
						t_env_var **env_vars);
t_env_var			*handle_tokens_in_prompt(char **commands,
						t_env_var **env_vars);
void				handle_pipe_and_red(t_list_token *data, t_env_var *vars);

			// -----HANDLE ENV-VARS--------
void				free_vars(t_env_var *vars);
t_env_var			*get_env_vars(char **envp);
t_env_var			*add_env_var(t_env_var *old_env_vars, char *word);
t_env_var			*delete_env_var(t_env_var *old_env_vars, char *key);
char				*get_key_from_word(char *word);
char				*get_value_from_var(char *word, t_env_var *vars);
bool				check_if_alphanumeric(char *str);
			//---------BUILTINS-----------
void				mini_echo(char **commands, t_env_var *vars);
int					mini_cd(char **commands, t_env_var *vars);
void				mini_pwd(void);
void				mini_exit(char **commands, int last_exit_status);
void				mini_env(t_env_var *env_vars);
t_env_var			*mini_unset(char **commands, t_env_var *env_vars);
t_env_var			*mini_export(char **commands, t_env_var **env_vars);

			//---------- token assignation----------
t_token_type		check_token(char *str);
void				assign_token_to_list(char *line, t_token_type token,
						t_list_token **data);
void				prepare_for_tokenization_quote(char *str,
						t_list_token **data,
						t_token_type token);
void				prepare_for_tokenization_word(char *str,
						t_list_token **data,
						t_token_type token);

// ------------------------ceva --------------
char				**turn_word_into_arr(t_list_token *data);
void				handle_not_existent_builtins(t_list_token *data,
						t_env_var **var);

//-------------------custom_split---------------
char				**custom_split(const char *str, char c);

int					allocate_for_strings(const char *str, char c);

// --------------------SPLIT_utils-------------------

void				update_word_flag1(t_info *p, const char *str);
void				update_word_flag2(t_info *p, const char *str,
						char c);
void				init_info_dat(t_dat *p);
void				init_info(t_info *p);

//-------------------SPLIT_utils2--------------------

void				skip_word_quotes(t_dat *indexes,
						t_word_info *word_info, char *str);
int					allocate_memory(char *str, char c,
						t_word_info *word_info);
void				process_string(char *str, t_dat *indexes,
						t_word_info *word_info, char c);
void				finalize_word_info(t_dat *indexes,
						t_word_info *word_info);

//----------------HANDLE_PIPE---------
bool				check_for_pipe_in_line(t_list_token *data);
t_env_var			*handle_pipe(t_list_token *data, t_env_var *env_vars);

//----------------HANDLE_PIPE2___________
int					count_nb_of_pipes(t_list_token *data);
char				**fill_argv_array_pipe(t_list_token *data,
						char **argv, int count);
char				**convert_tokens_to_argv(t_list_token *data);
int					count_commands(t_list_commands *cmd);
void				cleanup_pipes_and_wait(int (*pipes)[2], int num_cmds);

// -------------------exec_utils
bool				check_if_builtin(char *word);

// -----------------handle_builtins_type-----------
int					execute_builtins_with_no_output(char **commands,
						t_env_var *vars);
int					execute_builtins_with_output(char **commands,
						t_env_var *vars);
t_env_var			*exec_env_var_fct(char **commands, t_env_var *vars);
bool				check_for_env_commands(char **commands);

// -----------------simple comands-----------
void				execute_process(char *path, char **argv, t_env_var *vars);
t_env_var			*exec_line(t_list_token *data, t_env_var *vars);

// --------------------get_path-----------
char				*get_env_path(t_env_var *env_vars);
char				*get_path(char *command, t_env_var *env_vars);

///--------------------- exec_pipe-------------
// t_env_var			*execute_commands(t_list_commands *current,
// 						int (*pipes)[2], t_env_var *env_vars, int i);
t_env_var			*execute_commands(t_list_commands *current,
						int (*pipes)[2], t_env_var *vars);
void				check_pid(t_env_var *vars, int (*pipes)[2]);

//---------------------redirects--------------------
bool				check_for_redirects_in_line(t_list_token *data);
void				handle_redirects(t_list_token *data, t_env_var *vars);
void				execute_command_red( t_list_commands_red *cmd,
						t_env_var *vars);
t_list_commands_red	*initialize_new_cmd(void);
void				execute_command_red(t_list_commands_red *cmd,
						t_env_var *vars);
void				execute_child_process(t_list_commands_red *cmd,
						t_env_var *vars);
void				check_path_fail_red(char *path, t_list_commands_red *cmd);
void				fd_handeler(t_list_commands_red *current_cmd,
						t_list_commands_red *last_cmd);
char				**convert_tokens_to_argv_red(t_list_token *data);
t_list_commands_red	*initialize_new_cmd(void);
void				input_file_from_temp(void);
void				handle_heredoc(char *delimiter);
void				output_file(char *red, char *output_file, int is_last);
void				input_file(char *input_file);
///-----------------helper_functions---------
void				free_exec_args(char *path, char **argv);
t_env_var			*remove_env_var(char *command, t_env_var *env_vars);
int					ft_strcmp(char *s1, char *s2);
void				*ft_memset(void *b, int c, size_t len);
// char				*ft_strchr(char *s, int c);

///-----------------helper_functions_exec---------
void				free_command_list(t_list_commands *cmd_head);
t_list_commands		*handle_malloc_fail(t_list_commands *new_cmd,
						t_list_token *current);
//----------split_for_path------------
char				**ft_split(char const *s, char c);

#endif
