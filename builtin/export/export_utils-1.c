/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils-1.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 00:20:38 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/29 23:08:49 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_var_value_checker(char *str)
{
	int	i;

	i = -1;
	if (is_there_quotes(str))
		return (1);
	else if (ft_is_whitespace(str[i]))
		return (0);
	else
	{
		while (str[i] && !ft_is_whitespace(str[i]))
			i++;
		
	}
	return (0);
}

int	export_var_name_checker(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (!is_valid_var_first_char(str[i])
			&& (i == 0 && ft_is_whitespace(str[i - 1])))
		{
			printf("minishell: export: `%s': not a valid identifier\n", str);
			return (0);
		}
	}
	return (1);
}

char	*extract_var_name(char *str, int i)
{
	int	c;

	c = i;
	while (i > 0 && str[i] != '=')
		i--;
	while (c > 0 && !ft_is_whitespace(str[c - 1]))
		c--;
	return (ft_substr(str, c, (i - c)));
}

char	*extract_var_value(char *str, int i)
{
	int	c;

	c = i;
	while (c > 0 && str[c - 1] != '=')
		c--;
	if (i - c == 0)
		return (NULL);
	return (ft_substr(str, c, (i - c)));
}

char	*export_extract_arg(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isalpha(str[i]))
		i++;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (!str[i])
		return (NULL);
	return (ft_substr(str, i, (ft_strlen(str) - i)));
}
