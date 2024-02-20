/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:07:01 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/19 16:11:30 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_manager(t_data *data)
{
	int		i;
	char	**cmd_argument;

	data->index_redirs = ((i = 0));
	cmd_argument = NULL;
	if (data->n_cmds == 1)
	{
		if (single_arg(data, cmd_argument) == -1)
			return (-1);
	}
	else if (data->n_cmds >= 1)
	{
		if (pipex_exec(data) == -1)
			return (-1);
	}
	return (0);
}

int	builtin_checker(char *tmp)
{
	int		token;

	token = 0;
	if (ft_strncmp(tmp, "cd", 2) == 0)
		token = 1;
	if (ft_strncmp(tmp, "echo", 4) == 0)
		token = 2;
	else if (ft_strncmp(tmp, "env", 3) == 0)
		token = 3;
	else if (ft_strncmp(tmp, "exit", 4) == 0)
		token = 4;
	else if (ft_strncmp(tmp, "export", 6) == 0)
		token = 5;
	if (ft_strncmp(tmp, "pwd", 3) == 0)
		token = 6;
	else if (ft_strncmp(tmp, "unset", 5) == 0)
		token = 7;
	return (token);
}

void	builtin_manager(t_data *tmp, int token)
{
	if (token == 1)
		execute_cd(tmp);
	else if (token == 2)
		execute_echo(tmp);
	else if (token == 3)
		execute_env(tmp);
	else if (token == 4)
		execute_exit(tmp);
	else if (token == 6)
		execute_pwd(tmp);
	else if (token == 5)
		execute_export(tmp);
	else if (token == 7)
		execute_unset(tmp);
}

	// else
		// builtin_checker(data);
	// printf("hey = %d\n", data->n_cmds);
	// fprintf(stderr, "%d\n", data->n_cmds);
	// if (data->n_cmds == 1)
	// 	single_arg(data);
	// if (data->n_cmds >= 2)
	// 	Pipex_Exec(data);
	// i++;
	// else if (token == 2)
	// 	command_exec();
	// else if (token == 3)
	// 	return (printf("Wrong input\n"), 1);


/*
int	builtin_checker(t_data *tmp)
{
	int		token;

	token = 0;
	if (ft_strncmp(tmp->input, "cd", 2) == 0
		&& (tmp->input[2] == '\0' || ft_is_whitespace(tmp->input[2])))
		token = 1;
	if (ft_strncmp(tmp->input, "echo", 4) == 0
		&& (tmp->input[4] == '\0' || ft_is_whitespace(tmp->input[4])))
		token = 2;
	else if (ft_strncmp(tmp->input, "env", 3) == 0
		&& (tmp->input[3] == '\0' || ft_is_whitespace(tmp->input[3])))
		token = 3;
	else if (ft_strncmp(tmp->input, "exit", 4) == 0
		&& (tmp->input[4] == '\0' || ft_is_whitespace(tmp->input[4])))
		token = 4;
	else if (ft_strncmp(tmp->input, "export", 6) == 0
		&& (tmp->input[6] == '\0' || ft_is_whitespace(tmp->input[6])))
		token = 5;
	if (ft_strncmp(tmp->input, "pwd", 3) == 0
		&& (tmp->input[3] == '\0' || ft_is_whitespace(tmp->input[3])))
		token = 6;
	else if (ft_strncmp(tmp->input, "unset", 5) == 0
		&& (tmp->input[5] == '\0' || ft_is_whitespace(tmp->input[5])))
		token = 7;
	return (token);
}
*/