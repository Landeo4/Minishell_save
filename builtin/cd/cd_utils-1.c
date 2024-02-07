/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils-1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 05:27:00 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/30 09:25:19 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cd_extract_arg(char *str)
{
	int		i;
	int		c;
	char	*cd_path;

	i = 0;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	while (str[i] && !ft_is_whitespace(str[i]))
		i++;
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	c = i;
	if (str[i] == '"' || str[i] == 39)
	{
		c = quoted_arg_util(str, c);
		cd_path = ft_substr(str, i + 1, c - 3);
	}
	else
	{
		while (str[c] && !ft_is_whitespace(str[c]))
			c++;
		cd_path = ft_substr(str, i, c);
	}
	return (cd_path);
}

int	quoted_arg_util(char *str, int c)
{
	if (str[c] == 39)
	{
		c++;
		while (str[c] && str[c] != 39)
			c++;
	}
	else if (str[c] == '"')
	{
		c++;
		while (str[c] && str[c] != '"')
			c++;
	}
	if (str[c] == '"' || str[c] == 39)
		c--;
	return (c);
}

void	error_handling(int err, char *str, t_data *data)
{
	if (err == 2)
		printf("minishell: cd: %s: No such file or directory.\n", str);
	else if (err == 20)
		printf("minishell: cd: %s: is not a directory.", str);
	else if (err == 13)
		printf("minishell: cd: %s: Permission denied.\n", str);
	free(str);
	exit_status_updater(data, err, NULL, NULL);
}
