/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:38:26 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/06 12:21:17 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_redirs_ac(char *input)
{
	int		nb;
	int		i;

	i = nb = 0;
	while (input[i])
	{
		if (input[i] == '>' || input[i] == '<')
			nb++;
		i++;
	}
	return (nb);
}

int	get_kind_redirs_ac(char *input)
{
	int		in;
	int		out;
	int		i;

	i = ((out = 0));
	in = 0;
	while (input[i])
	{
		if (input[i] == '>')
			out++;
		if (input[i] == '<')
			in++;
		i++;
	}
	if (in > 0 && out > 0)
		return (3);
	else if (in > 0)
		return (1);
	else if (out > 0)
		return (2);
	return (0);
}
