/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_found.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 20:37:01 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/20 09:39:20 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	first_redirect(t_data *data, char *input, int count)
{
	int		i;
	int		j;
	int		check;

	i = 0;
	check = 0;
	j = -1;
	if (data->n_redirs > 0)
		check = first_redirect_helper(input, j, i);
	if (check == -1)
		return (-1);
	check = check + count;
	return (check);
}

int	first_redirect_helper(char *input, int j, int i)
{
	int		check;

	check = -1;
	while (input[i])
	{
		while (ft_is_whitespace(input[i]))
			i++;
		if (input[i] == '<' || input[i] == '>')
		{
			j++;
			if (input[i] == '<')
				check = j;
			i++;
		}
		if (!input[i])
			break ;
		i++;
	}
	return (check);
}

int	last_redirect(t_data *data, char *input, int count)
{
	int		i;
	int		j;
	int		check;

	i = 0;
	check = 0;
	j = -1;
	if (data->n_redirs > 0)
		check = last_redirect_helper(input, j, i);
	if (check == -1)
		return (-1);
	check = check + count;
	return (check);
}

int	last_redirect_helper(char *input, int j, int i)
{
	int		check;

	check = -1;
	while (input[i])
	{
		while (ft_is_whitespace(input[i]))
			i++;
		if (input[i] == '<' || input[i] == '>')
		{
			j++;
			if (input[i] == '>' || (input[i] == '>' &&
				input[i + 1] == '>'))
				check = j;
			i++;
		}
		if (!input[i])
			break ;
		i++;
	}
	return (check);
}
