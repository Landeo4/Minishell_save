/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils-5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:22:47 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/19 10:26:30 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_double_tab_len(char **splitted)
{
	int	i;

	i = 0;
	while (splitted[i])
		i++;
	return (i);
}

int	cmd_counter(char **splitted)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (splitted[i])
	{
		if (splitted[i][0] == '<' || splitted[i][0] == '>')
			count -= 2;
		i++;
		count++;
	}
	return (count);
}

void	heredoc_counter(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (data->input[i] == '<' && data->input[i + 1] == '<')
		{
			i += 2;
			data->nb_here_doc++;
		}
		i++; 
	}
}