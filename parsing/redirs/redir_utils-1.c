/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils-1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 19:31:35 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/14 10:23:28 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirection_and_expand_handler(t_data *data)
{
	if (is_there_backslash(data->input) || is_there_dollar(data->input)
		|| is_there_quotes(data->input) || is_there_tilde(data->input))
		expand_handler(data);
	if (ft_strlen(data->input) == 0)
	{
		free(data->input);
		data->input = NULL;
	}
	if (!data->input)
		return (0);
	if (is_there_redirs(data->input))
	{
		if (!is_valid_redir(data->input, data))
			return (0);
		redirection_counter(data);
		if (data->n_redirs != 0)
			redirection_parser(data);
		if (are_token_sep_by_wspace(data->input))
			extract_redir_cmds(ft_split(data->input, ' '), data);
		else
			extract_redir_no_wspace(data, r_word_counter(data, 0, 1));
	}
	return (1);
}

int	is_valid_redir(char *str, t_data *data)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!is_in_quotes(str, i) && ((str[i] == '>' && str[i + 1] != '>')
				|| (str[i] == '<' && str[i + 1] != '<')))
		{
			i ++;
			if (!redir_checker(str, i, data))
				return (0);
		}
		else if (!is_in_quotes(str, i) && ((str[i] == '>' && str[i + 1] == '>')
				|| (str[i] == '<' && str[i + 1] == '<')))
		{
			i ++;
			if (!redir_checker(str, i, data))
				return (0);
		}
		i++;
	}
	return (1);
}

void	redirection_counter(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i])
	{
		if (!is_in_quotes(data->input, i))
		{
			if ((data->input[i] == '<' && data->input[i + 1] != '<')
				|| (data->input[i] == '>' && data->input[i + 1] != '>'))
			{
				data->n_redirs++;
				i++;
			}
			else if ((data->input[i] == '<' && data->input[i + 1] == '<')
				|| (data->input[i] == '>' && data->input[i + 1] == '>'))
			{
				data->n_redirs++;
				i += 2;
			}
		}
		if (i < (int)ft_strlen(data->input))
			i++;
	}
}

void	redirection_parser(t_data *data)
{
	int	i;

	i = 0;
	data->tab = malloc(sizeof (int *) * (data->n_redirs + 1));
	if (!data->tab)
		return ;
	data->n = data->n_redirs;
	while (i < data->n_redirs)
	{
		data->tab[i] = malloc(sizeof (int) * 3);
		i++;
	}
	data->tab[i] = NULL;
	get_redir_infos(data, 0, 0);
}
