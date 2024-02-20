/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_utils3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 16:38:26 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/20 13:51:27 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_nb_redirs_ac(char *input)
{
	int		nb;
	int		i;

	i = ((nb = 0));
	while (input[i])
	{
		if (input[i] == '>')
		{
			if (input[i + 1] == '>')
				i++;
			nb++;
		}
		if (input[i] == '<')
		{
			if (input[i + 1] == '<')
				i++;
			nb++;
		}
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

int	len_buf(char *buf, char *input, t_data *data, int act_redir)
{
	int		len;
	int		i;

	(void)data;
	(void)act_redir;
	(void)buf;
	len = ((i = 0));
	while (input[i])
	{
		if (input[i] == ' ' && input[i + 1] == '>')
		{
			i += 3;
			while (ft_isalnum(input[i]))
				i++;
			if (!input[i])
				break ;
		}
		len++;
		i++;
	}
	if (input[i] == ' ')
		len--;
	return (len);
}

void	close_all_redirs(t_data *data)
{
	int		i;
	int		j;

	j = 0;
	i = data->n_redirs;
	fprintf(stderr, "%d\n", data->n_redirs);
	// fprintf(stderr, "donc la %d t je dois atteindre %d\n", j, i);
	while (j < i)
	{
		fprintf(stderr, "donc la %d t je dois atteindre %d\n", j, i);
		close(data->tab[j][2]);
		j++;
	}
	
}
