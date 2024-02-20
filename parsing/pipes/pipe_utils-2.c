/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils-2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 06:25:09 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/12 08:54:23 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_piped_input_valid(char *str, t_data *data)
{
	if (!is_valid_pipe(str, data))
		return (0);
	else if (!is_pipe_content_valid(str, data))
		return (0);
	return (1);
}

int	is_pipe_content_valid(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		while (str[i] && !ispipe(str[i]))
			i++;
		if (ispipe(str[i]))
			i++;
		while (str[i] && ft_is_whitespace(str[i]))
			i++;
		if (ispipe(str[i]) && !is_in_quotes(str, i))
		{
			set_status(data, 2, "syntax error near unexpected token `|'", NULL);
			return (0);
		}
	}
	return (1);
}
