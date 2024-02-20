/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:29:11 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/19 14:18:18 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_manager(t_data *data, int key)
{
	if (key == 1)
	{
		if (data->pr->input)
			free(data->pr->input);
		if (data->input)
			free(data->input);
	}
	else if (key == 2)
	{
		if (data->cmds)
			free_cmds(data);
		if (data->pr->input)
			free(data->pr->input);
	}
	if (data->cmds)
		free_cmds(data);
	if (data->redir_tab)
		ft_split_free(data->redir_tab);
	if (data->tab)
		free_tab(data->tab);
}

void	free_master(t_data *data)
{
	if (data->input)
		free(data->input);
	free_input_lst(data->inp);
}

void	free_input_lst(t_input *lst)
{
	t_input	*tmp;

	tmp = NULL;
	while (lst)
	{
		tmp = lst->next;
		if (lst->str)
			free(lst->str);
		free(lst);
		lst = tmp;
	}
}

void	free_end_of_program(t_prompt *p)
{
	if (p->user)
		free(p->user);
	if (p->w_d)
		free(p->w_d);
	if (p->post)
		free(p->post);
	if (p->env)
		free_env(p->env);
	if (p->nv)
		free_env_tab(p->nv);
	if (p->name)
		free(p->name);
	if (p->pid)
		free(p->pid);
	if (p->data->c_status)
		free(p->data->c_status);
}
