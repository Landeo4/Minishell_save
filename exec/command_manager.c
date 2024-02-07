/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_manager.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 18:07:01 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/06 13:16:30 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	command_manager(t_data *data)
{
	int	check;

	check = builtin_checker(data);
	if (check != 0)
		builtin_manager(data, check);
	else if (data->n_cmds == 1)
		single_arg(data);
	else if (data->n_cmds >= 1)
		pipex_exec(data);
	return (0);
}

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
		execute_pwd();
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