/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils-1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 03:12:41 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/05 11:06:09 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unclosed_quote_detector(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 39)
		{
			i++;
			while (str[i] && str[i] != 39)
				i++;
			if (str[i] != 39)
				return (pr_error("input error : unclosed single quote."));
		}
		else if (str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			if (str[i] != '"')
				return (pr_error("input error : unclosed double quote."));
		}
		i++;
	}
	return (1);
}

int	is_in_quotes(char *str, int c)
{
	int	i;
	int	q_flag;

	i = 0;
	q_flag = 0;
	while (str[i] && i < c)
	{
		if (str[i] == 39)
		{
			if (q_flag == 0)
				q_flag = 1;
			else if (q_flag == 1)
				q_flag = 0;
		}
		else if (str[i] == '"')
		{
			if (q_flag == 0)
				q_flag = 2;
			else if (q_flag == 2)
				q_flag = 0;
		}
		i++;
	}
	return (q_flag);
}

int	is_there_quotes(char *str)
{
	int	i;

	i = -1;
	if (!str)
		return (0);
	while (str[++i])
		if ((str[i] == '"' || str[i] == 39) && is_in_quotes(str, i))
			return (1);
	return (0);
}
