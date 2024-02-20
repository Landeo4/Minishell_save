/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 14:57:24 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/20 14:45:14 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	child_process(t_data *data, int **pipefd, int i, char **cmd_argument)
{
	char	*cmd_arg;

	if (ft_pipex_helper_dup(data, pipefd, i) == -1)
	{
		free(cmd_argument);
		ft_freedb(data->actual_path);
		return (-1);
	}
	if (check_redirection_now(data, i) == 0)
		cmd_arg = data->redir_tab[i];
	else
		cmd_arg = data->cmds[i];
	cmd_argument = ft_split(cmd_arg, ' ');
	if (builtin_checker(data->cmds[i]) > 0)
	{
		builtin_multi(data);
		fprintf(stderr, "voici le pipe actuel %s\n", data->cmds[i]);
		builtin_manager(data, builtin_checker(data->cmds[i]));
		free_multi_struct_and_arg(data, cmd_argument, pipefd);
		return (-1);
	}
	// if (data->cmd_valid == -1)
	// {
	// 	cmd_not_valid(data);
	// 	exit(data->status_code);
	// }
	// cree un if qui contiens checker de builtin
	execve(data->actual_path[i], cmd_argument, data->pr->nv);
	free_all_pipe(pipefd);
	exit(0);
	return (0);
}

int	ft_pipex_helper_dup(t_data *data, int **pipefd, int i)
{
	int		check;

	check = 0;
	if (i % 2 == 0)
		check = child_process_in(pipefd, data, i, 0);
	else if (i % 2 == 1)
		check = child_process_in(pipefd, data, i, 1);
	if (check == -1)
		return (-1);
	return (0);
}

int	builtin_multi(t_data *data)
{
	int	check;

	check = builtin_checker(data->input);
	if (check >= 1 && check <= 7)
	{
		if (data->n_redirs > 0)
		{
			data->first = malloc(sizeof(int) * 1);
			data->last = malloc(sizeof(int) * 1);
			data->first[0] = first_redirect(data, data->input, 0);
			data->last[0] = last_redirect(data, data->input, 0);
			redirection_dup1_in(data, data->first[0], data->last[0]);
		}
		builtin_manager(data, check);
		if (data->n_redirs > 0)
		{
			free(data->first);
			free(data->last);
		}
		return (-1);
	}
	return (0);
}

// int	cmd_not_valid(t_data *data)
// {
	
// }
