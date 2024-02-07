/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 08:35:01 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/28 23:26:37 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_sbase(t_prompt *ptr, char **env)
{
	char				*tmp;
	t_env				*env_l;
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	ft_memset(&sa_int, 0, sizeof(struct sigaction));
	ft_memset(&sa_quit, 0, sizeof(struct sigaction));
	sa_int.sa_handler = handle_signals;
	sa_quit.sa_handler = handle_signals;
	sigaction(SIGINT, &sa_int, NULL);
	sigaction(SIGQUIT, &sa_quit, NULL);
	env_l = malloc(sizeof(t_env));
	if (!env_l)
		return (ptr->env = NULL, 0);
	else
	{
		if (!put_env_to_lst(env_l, env))
			return (ptr->env = NULL, 0);
		ptr->user = getenv("LOGNAME");
		tmp = getenv("SESSION_MANAGER");
		ptr->post = ft_substr(tmp, 6, 12);
		ptr->w_d = getcwd(NULL, 0);
	}
	return (ptr->env = env_l, 0);
}

void	init_extras(t_prompt *ptr)
{
	ptr->name = ft_strdup("minishell");
	ptr->pid = ft_itoa((int)getpid());
	create_side_env(ptr);
}

int	init_str(t_data *data, t_prompt *prompt)
{
	data->head = NULL;
	data->new_head = NULL;
	data->tail = NULL;
	data->to_add = NULL;
	data->i_status = 0;
	data->c_status = ft_itoa(data->i_status);
	data->n_redirs = 0;
	data->input = prompt->input;
	data->pr = prompt;
	data->env = prompt->env;
	return (1);
}

int	init_str_pipe(t_data *data, t_prompt *prompt)
{
	data->head = NULL;
	data->new_head = NULL;
	data->tail = NULL;
	data->to_add = NULL;
	data->i_status = 0;
	data->c_status = ft_itoa(data->i_status);
	data->n_redirs = 0;
	data->pr = prompt;
	data->input = prompt->input;
	data->env = prompt->env;
	return (1);
}
