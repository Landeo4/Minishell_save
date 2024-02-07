/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils-1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 04:25:22 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/28 23:24:41 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->n_cmds)
	{
		free(data->cmds[i]);
		i++;
	}
	free(data->cmds);
}

void	free_env(t_env	*env)
{
	t_env	*tmp;

	tmp = NULL;
	while (env)
	{
		tmp = env->next;
		free(env->var);
		free(env);
		env = tmp;
	}
}

void	free_env_tab(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	free(env);
}
