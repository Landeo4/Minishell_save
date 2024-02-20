/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_here.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 21:47:57 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/18 19:31:43 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_redirection_now(t_data *data, int i)
{
	int	j;

	j = 0;
	while (data->cmds[i][j])
	{
		if (data->cmds[i][j] == '>' || data->cmds[i][j] == '<')
			return (0);
		j++;
	}
	return (-1);
}

int	redirection_manager(t_data *data, int i)
{
	int		token;

	token = get_nb_redirs_ac(data->cmds[i]);
	fprintf(stderr, "voici index %d\n", data->index_fd);
	if (token > 0)
		redirection_dup1_in(data, data->first[data->index_fd], data->last[data->index_fd]);
	return (0);
}

int	is_redirect_actual(char *input)
{
	int		i;
	int		token;

	i = ((token = 0));
	while (input[i])
	{
		if (input[i] == '>')
		{
			token++;
			if (input[i + 1] == '>')
				i++;
		}
		else if (input[i] == '<')
		{
			token++;
			if (input[i + 1] == '<')
				i++;
		}
		i++;
	}
	return (token);
}
