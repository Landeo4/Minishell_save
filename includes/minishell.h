/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:35:12 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/07 11:13:37 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/includes/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <errno.h>

# ifndef G_STATUS
#  define G_STATUS

extern int	g_status;

# endif

// ! ---------------------------------------------------------------------------
// ?							STRUCTURES DECLARATION
// ! ---------------------------------------------------------------------------

struct		s_parse;
typedef struct s_struct
{
	char			*name;
	char			*pid;
	char			*input;
	char			*user;
	char			*post;
	char			*w_d;
	char			**nv;
	struct s_parse	*data;
	struct s_env	*env;
}	t_prompt;

typedef struct s_env
{
	char			*var;
	struct s_env	*next;
}	t_env;

typedef struct s_parse
{
	t_prompt		*pr;
	t_env			*env;
	char			*input;
	char			*head;
	char			*new_head;
	char			*tail;
	char			*to_add;
	char			**cmds;
	int				n_cmds;
	int				i_status;
	char			*c_status;
	int				**tab;
	char			**redir_tab;
	int				n_redirs;
	int				nb_redirs_ac;
	int				i;
	char			**actual_path;
	int				index_redirs;
	int				nb_here_doc;
	struct s_parse	*next;
}	t_data;

// ! ---------------------------------------------------------------------------
// ?							INITIALIZATION
// ! ---------------------------------------------------------------------------

int		main(int argc, char **argv, char *envp[]);
void	get_input(char **envp);
int		init_sbase(t_prompt *prompt, char **env);
void	init_extras(t_prompt *ptr);
int		init_str(t_data *data, t_prompt *prompt);
int		init_str_pipe(t_data *data, t_prompt *prompt);

// ! ---------------------------------------------------------------------------
// ?							INPUT PARSING
// ! ---------------------------------------------------------------------------

void	input_parser(t_prompt *prompt);
int		get_cmd(t_data *data);
int		invalid_character_checker(int c);
int		is_input_valid(char *str);
int		is_piped_input_valid(char *str);
int		exception_checker(char *str);
int		exception_checker_2(char *str, int i);
int		unclosed_quote_detector(char *str);

void	expand_handler(t_data *data);
int		expand_is_valid_char(int c);
int		is_valid_char(int c);
int		is_valid_char_after_redir(int c);
void	reg_expander(t_data *data);
void	reg_expand_splitter(t_data *data, int i);
void	reg_expand_joiner(t_data *data);
void	tilde_expander(t_data *data, int i);
void	backslash_expander(t_data *data, int i);
void	search_and_split(t_data *data, int i);
char	*quote_remover(t_data *data);
char	*quote_remover_v2(char *str);
int		empty_quote_handler(char *str);
void	quote_flagger(char *str, int i, int q_flag);

// ! ---------------------------------------------------------------------------
// ?							PARSING UTILS
// ! ---------------------------------------------------------------------------

void	ft_printlst(t_env *L);
void	exit_status_updater(t_data *data, int status, char *str, char *cmd);
char	*ft_get_env(t_env *env, char *str);
t_env	*ft_get_env_node(t_env *env, char *str);
int		put_env_to_lst(t_env *env, char **envp);
void	create_side_env(t_prompt *ptr);
void	add_var_to_env(t_data *data, char *var);
void	del_var_from_env(t_data *data, char *var);
int		env_len(t_env *env);
int		is_there_pipe(t_prompt *prompt);
int		is_there_dollar(char *str);
int		is_there_backslash(char *str);
int		is_there_quotes(char *str);
int		is_there_redirs(char *str);
int		is_there_tilde(char *str);
int		ispipe(int c);
int		is_valid_pipe(char *str);
int		is_in_quotes(char *str, int c);
int		is_pipe_content_valid(char *str);
char	**pipes_splitter(char const *s, char c, t_data *data);
int		n_args(char *str);
int		quote_skipper(char *str, int c);
int		is_valid_redir(char *str);
int		redir_checker(char *str, int i);
void	redirection_counter(t_data *data);
void	redirection_parser(t_data *data);
void	get_redir_infos(t_data *data);
void	set_tab_values(t_data *data, int n, int i, int mode);
char	*file_name_finder(t_data *data, int i, int c);
int		redirection_and_expand_handler(t_data *data);
void	tab_value_setter_double(t_data *data, int n, int i);
void	extract_redir_cmds(char **splitted, t_data *data);
int		cmd_counter(char **splitted);

// ! ---------------------------------------------------------------------------
// ?							SIGNAL HANDLER
// ! ---------------------------------------------------------------------------

void	handle_signals(int signum);

// ! ---------------------------------------------------------------------------
// ?							Command
// ! ---------------------------------------------------------------------------

int		command_manager(t_data *data);
int		builtin_checker(t_data *tmp);
void	builtin_manager(t_data *tmp, int token);

int		pipex_exec(t_data *data);
int		ft_pipex(t_data	*data, int i, char **cmd_argument);
int		**alloc_pipe(int i, int **pipefd);
int		**parent_process(int **pipefd, int i);
int		len_fd_tab(char	**str, int i);
int		verif_arg_fd(char *argv[], int i);
char	*str_join_free(char *path, char *cmd);
void	ft_freedb(char **str);
void	free_all_pipe(int **pipefd);
int		check_dup(int pipe, int token, int pipe2, t_data *data);
int		child_process_in(int **pipefd, t_data *data, int i, int token);
char	*arg(char *str, t_data *data);
int		ft_create_fd(char *argv, int flag);
char	**ft_get_path(char **env);
char	*ft_do_process(char *envp[], char *cmd);
int		child_process_in_or_out(int **pipefd, t_data *data, int i, int token);
int		child_process_middle(int **pipefd, t_data *data, int token);
int		redirection_manager(t_data *data, int i);
int		check_redirection_now(t_data *data, int i);
int		len_db_tab(char **str);
char	*copy_arg(char *dest, char *src);
char	*arg_helper(char **buf, char *tmp, t_data *data, int i);
char	*ft_strjoin_help(char **path, char *cmd, int i);
char	*ft_essaie(t_data *data, char *input);
char	*ft_essaie_helper(char *buf, char *input, int , t_data *data);
int		ft_count_space(char *buf);
int		redirection_single_chev(t_data *data, char *input);
int		len_buf(char *buf, char *input, t_data *data, int act_redir);
int		get_nb_redirs_ac(char *input);
void	close_all_pipe(int **pipefd, t_data *data);
int		first_redirect(t_data *data, char *input);
int		last_redirect(t_data *data, char *input);
int		is_redirect_actual(char *input);
int		redirection_dup_1(t_data *data, int first, int last);
int		redirection_dup_2(t_data *data, int first, int last);
void	free_single(t_data *data, char **cmd_argument, char *buf, char *fre);
int		redirection_here_doc(t_data *data, char *input);
char    *ft_do_here_doc(t_data *data);
char	*get_name_heredoc();
int		ft_make_here_doc(t_data *data, int file);
char	*get_flag_here(t_data *data);
char	*main_here_doc(t_data *data);
int		get_kind_redirs_ac(char *input);
int		ft_do_process_helper(char *cmd);
int		ft_check_access(t_data *data, int i);
void	free_all_fd(t_data *data);

// ! ---------------------------------------------------------------------------
// ?							Single_Pipe
// ! ---------------------------------------------------------------------------

int		single_arg(t_data *data);
int		exec_single(char **cmd_argument, char *fre, t_data *data);
int		redirection_single(t_data *data);
char	**espoir(char **cmd_argument);
int		found_max(char **cmd_argument);

// ! ---------------------------------------------------------------------------
// ?							Builtin && Tools
// ! ---------------------------------------------------------------------------

void	execute_cd(t_data *data);
char	*cd_extract_arg(char *str);
int		quoted_arg_util(char *str, int c);
void	change_directory(t_data *data, char *path);
void	go_back_one_level(t_data *data);
void	update_vars(t_data *data);
void	error_handling(int err, char *str, t_data *data);

void	execute_echo(t_data *data);
int		is_wspace_or_null(char *str, int i);
int		flag_skipper(char *str);

void	execute_pwd(void);
void	execute_env(t_data *data);

void	execute_export(t_data *data);
char	*export_extract_arg(char *str);
void	export_no_args(t_env *env);
int		export_valid_args_counter(char *str);
int		export_is_valid_arg(char *str, int i);
void	export_error_handler(char *str, char *to_check, char *rest);
char	*extract_var_name(char *str, int i);
char	*extract_var_value(char *str, int i);
int		export_var_name_checker(char *str);
int		is_valid_var_first_char(int c);
int		is_valid_var_char(int c);
int		is_valid_var_name(char *var);
char	*export_finalizer(char *args, int i, t_data *data);
void	do_export(char *var_name, char *var_value, t_data *data);

void	execute_unset(t_data *data);
char	*unset_extract_var_name(char *args, int i);
int		unset_var_name_skipper(char *args, int i);
void	do_unset(char *args, t_data *data);


int		execute_exit(t_data *data);

// void	execute_export();
// int		execute_exit();

// ! ---------------------------------------------------------------------------
// ?							Utils Free
// ! ---------------------------------------------------------------------------

void	free_manager(t_data *data, int key);
void	free_cmds(t_data *data);
void	free_env(t_env	*env);
void	free_env_tab(char **env);
void	free_end_of_program(t_prompt *p);

#endif