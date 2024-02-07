/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils-2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:30:26 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/06 13:27:19 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_checker(char *str, int i)
{
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '\0')
		return (pr_error("parse error near '\\n'"));
	else if (!is_valid_char_after_redir(str[i]))
		return (pr_error("syntax error near unexpected token `\\n'"));
	else if ((str[i - 1] == '<' || str[i - 1] == '>')
		&& (str[i] == '<' || str[i] == '>') && str[i + 1] == '|')
		return (pr_error("syntax error near unexpected token `|'"));
	else if ((str[i] == '<' || str[i] == '>')
		&& (str[i - 1] != '<' || str[i - 1] != '>') && str[i + 1] == '|')
		return (pr_error("syntax error near unexpected token `|'"));
	else if (str[i - 1] == '<' && str[i] == '>'
		&& (i >= 2 && str[i - 2] != '<'))
		return (pr_error("parse error near '\\n'"));
	// else if (str[i] == '<' && str[i - 1] == '<')
	// 	return (pr_error("parse error near '<<'"));
	else if (str[i] == '>' && str[i - 1] == '>')
		return (pr_error("parse error near '>>'"));
	// else if (str[i] == '<' || (str[i] == '<' && str[i - 1] == '>'))
	// 	return (pr_error("parse error near '<'"));
	// else if (str[i] == '>' || (str[i] == '<' && str[i - 1] == '<'))
	// 	return (pr_error("parse error near '>'"));
	return (1);
}

int	is_there_redirs(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if ((str[i] == '>' || str[i] == '<') && is_in_quotes(str, i) != 1)
			return (1);
	return (0);
}

int	is_valid_char_after_redir(int c)
{
	if (c == '/')
		return (0);
	else if (ft_isprint(c))
		return (1);
	return (0);
}

void	extract_redir_cmds(char **splitted, t_data *data)
{
	int	i;
	int	c;
	int	count;

	i = 0;
	c = 0;
	count = cmd_counter(splitted);
	data->redir_tab = malloc(sizeof(char *) * (count + 1));
	if (!data->redir_tab)
		return ;
	while (splitted[c] && i < count)
	{
		if (splitted[c][0] == '<' || splitted[c][0] == '>')
			c += 2;
		data->redir_tab[i] = ft_strdup(splitted[c]);
		i++;
		c++;
	}
	data->redir_tab[i] = NULL;
	ft_split_free(splitted);
	return ;
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
