/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 06:15:38 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/26 23:06:28 by vsozonof         ###   ########.fr       */
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

int	multiple_pipe_checker(char *str, int i)
{
	if (ispipe(str[i]) && ispipe(str[i + 1]) && !ispipe(str[i + 2]))
		return (pr_error("`||' operator not handled"));
	else if (ispipe(str[i]) && ispipe(str[i + 1]) && ispipe(str[i + 2]))
		return (pr_error("syntax error near unexpected token `||'"));
	return (1);
}

int	is_valid_pipe(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (!multiple_pipe_checker(str, i))
		return (0);
	else if (ispipe(str[i]))
		return (pr_error("syntax error near unexpected token `|'"));
	while (str[i])
	{
		if (!is_in_quotes(str, i))
			if (ispipe(str[i]) && !multiple_pipe_checker(str, i))
				return (0);
		i++;
	}
	return (1);
}
