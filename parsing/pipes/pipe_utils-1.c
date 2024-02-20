/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils-1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 06:15:38 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/12 08:54:08 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_there_pipe(t_prompt *prompt)
{
	int	i;

	i = -1;
	while (prompt->input[++i])
		if (prompt->input[i] == '|' && !is_in_quotes(prompt->input, i))
			return (1);
	return (0);
}

int	ispipe(int c)
{
	if (c == '|')
		return (1);
	else
		return (0);
}

int	multiple_pipe_checker(char *str, int i, t_data *data)
{
	if (ispipe(str[i]) && ispipe(str[i + 1]) && !ispipe(str[i + 2]))
	{
		set_status(data, 2, "`||' operator not handled", NULL);
		return (0);
	}
	else if (ispipe(str[i]) && ispipe(str[i + 1]) && ispipe(str[i + 2]))
	{
		set_status(data, 2, "syntax error near unexpected token `||'", NULL);
		return (0);
	}
	return (1);
}

int	is_valid_pipe(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (!multiple_pipe_checker(str, i, data))
		return (0);
	else if (ispipe(str[i]))
	{
		set_status(data, 2, "syntax error near unexpected token `|'", NULL);
		return (0);
	}
	while (str[i])
	{
		if (!is_in_quotes(str, i))
			if (ispipe(str[i]) && !multiple_pipe_checker(str, i, data))
				return (0);
		i++;
	}
	return (1);
}
