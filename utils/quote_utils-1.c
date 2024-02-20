/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils-1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 03:12:41 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/13 06:50:40 by vsozonof         ###   ########.fr       */
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

void	unquote_command(t_data *data)
{
	char	*to_extract;
	char	*rest;
	int		i;

	i = 0;
	while (data->input[i])
	{
		if ((!is_in_quotes(data->input, i) && ft_is_whitespace(data->input[i])))
			break ;
		i++;
	}
	to_extract = ft_substr(data->input, 0, i);
	rest = ft_substr(data->input, (i), (ft_strlen(data->input)));
	free(data->input);
	data->input = to_extract;
	reg_expander(data, 0);
	to_extract = data->input;
	data->input = rest;
	reg_expander(data, 0);
	rest = data->input;
	if (to_extract && is_there_quotes(to_extract))
		to_extract = quote_remover_v2(to_extract);
	data->input = strjoin_and_free(to_extract, rest);
}
