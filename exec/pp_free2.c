/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:14:34 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/20 11:41:01 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_and_free(t_data *data, int **pipefd, int *pid)
{
	int	i;

	i = 0;
	while (i < data->n_cmds)
	{
		waitpid(pid[i], NULL, 0);
		i++;
	}
	free_all_pipe(pipefd);
	free_all_fd(data);
	free(pid);
}

// void	free_all_alloc(t_data *data)
// {
// 	if (data->n_redirs > 0)
// 	{
// 		free(data->first);
// 		free(data->last);
// 	}
// 	// free_manager(data, 0);
// 	//free tout
// }

void	free_single_struct_and_arg(t_data *data, char **cmd_argument, char *fre)
{
	(void)cmd_argument;
	(void)fre;
	// free_single(data, cmd_argument, fre);
	free_manager(data, 1);
	free_env_tab(data->pr->nv);
	free_env(data->env);
}

void	free_multi_struct_and_arg(t_data *data, char **cmd_argument, int **pipefd)
{
	ft_freedb(cmd_argument);
	(void)pipefd;
	// free_manager(data, 2);
	// free_env_tab(data->pr->nv);
	// free_env(data->env);
	ft_freedb(data->actual_path);
}
