/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exception_checker.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/09 04:37:37 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/05 11:13:14 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_input_valid(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '~')
		return (pr_error("/mnt/nfs/homes/vsozonof: Is a directory"));
	else if (str[i] == '\\')
		return (0);
	if (!invalid_character_checker(str[i]))
		return (0);
	else if (!exception_checker(str))
		return (0);
	else if (!unclosed_quote_detector(str))
		return (0);
	return (1);
}

int	invalid_character_checker(int c)
{
	if (c == '\0' || c == '!' || c == ':')
		return (0);
	else
		return (1);
}

int	exception_checker(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_in_quotes(str, i))
		{
			if (str[i] == '(')
				return (pr_error("syntax error near unexpected token `('"));
			else if (str[i] == ')')
				return (pr_error("syntax error near unexpected token `)'"));
			else if (str[i] == '*')
				return (pr_error("syntax error near unexpected token `*'"));
			else if (str[i] == '&' && str[i + 1] == '&')
				return (pr_error("syntax error near unexpected token `&&'"));
			else if (str[i] == '&')
				return (pr_error("syntax error near unexpected token `&'"));
			else if (!exception_checker_2(str, i))
				return (0);
		}
		i++;
	}
	return (1);
}

int	exception_checker_2(char *str, int i)
{
	if (str[i] == ';' && str[i + 1] == ';')
		return (pr_error("syntax error near unexpected token `;;'"));
	else if (str[i] == ';')
		return (pr_error("syntax error near unexpected token `;'"));
	return (1);
}
