/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils-4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 13:42:48 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/16 13:30:33 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	r_word_counter(t_data *data, int i, int j)
{
	while (data->input[i])
	{
		while (data->input[i] && ft_is_whitespace(data->input[i]))
			i++;
		if (!ft_is_whitespace(data->input[i]) && !is_token(data->input, i))
		{
			while (data->input[i] && !ft_is_whitespace(data->input[i])
				&& !is_token(data->input, i))
				i++;
			j++;
		}
		if (is_token(data->input, i))
		{
			while (data->input[i] && is_token(data->input, i))
				i++;
			j++;
		}
		if (i == (int)ft_strlen(data->input))
			break ;
		i++;
	}
	return (j);
}

int	is_token(char *str, int i)
{
	if (((str[i] == '>' && str[i + 1] != '>')
			|| (str[i] == '<' && str[i + 1] != '<'))
		|| (str[i] == '>' && str[i + 1] == '>')
		|| (str[i] == '<' && str[i + 1] == '<'))
		return (1);
	else
		return (0);
}

void	extract_redir_no_wspace(t_data *data, int n)
{
	char	**tab;
	int		i;
	int		j;
	int		c;

	j = ((c = 0));
	i = 0;
	tab = malloc(sizeof(char *) * n);
	if (!tab)
		return (set_status(data, 12, "malloc error.", NULL));
	data->new_head = ft_strdup(data->input);
	while (data->input[i] && j < (n - 1))
	{
		tab[j] = extract_word(data, 0, 0);
		j++;
	}
	free(data->new_head);
	tab[j] = NULL;
	extract_redir_cmds(tab, data);
}

char	*extract_word(t_data *data, int i, int c)
{
	char	*rest;
	char	*word;

	if (!data->new_head)
		return (NULL);
	while (data->new_head[i] && ft_is_whitespace(data->new_head[i]))
		i++;
	c = i;
	if (!is_token(data->new_head, i))
	{
		while (data->new_head[i] && !ft_is_whitespace(data->new_head[i])
			&& !is_token(data->new_head, i))
			i++;
	}
	else
		while (data->new_head[i] && is_token(data->new_head, i))
			i++;
	word = ft_substr(data->new_head, c, (i - c));
	rest = ft_substr(data->new_head, i, ft_strlen(data->new_head));
	free(data->new_head);
	data->new_head = rest;
	return (word);
}

int	double_redir_checker(char *str, int i, t_data *data)
{
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '\0')
		return (set_status(data, 2, "syntax error near `\\n'", NULL), 0);
	else if (str[i] == '>' || str[i] == '<')
		return (set_status(data, 2, "syntax error near `\\n'", NULL), 0);
	else if (str[i] == '|')
		return (set_status(data, 2, "syntax error near `|'", NULL), 0);
	return (1);
}
