/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils-2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 10:30:26 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/19 10:19:52 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ! Redirection Checker
// ? This function will check if the filename
// ? that follows a redirection token is valid or not
// * 1. \0
// * 2. >> ou << |
// * 3. > ou < |
// * 4. ><
// * 5. < >
// * 6. >> ou << et > >> < <<

int	redir_checker(char *str, int i, t_data *data)
{
	if (str[i] == str[i - 1])
		return (double_redir_checker(str, (i + 1), data));
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	if (str[i] == '\0')
		return (set_status(data, 2, "A. syntax error near `\\n'", NULL), 0);
	else if (str[i] == '>' || str[i] == '<')
		return (set_status(data, 2, "B. syntax error near `\\n'", NULL), 0);
	else if ((str[i - 1] == '<' || str[i - 1] == '>')
		&& (str[i] == '<' || str[i] == '>') && str[i + 1] == '|')
		return (set_status(data, 2, "syntax error near `|'", NULL), 0);
	else if ((str[i - 1] == '<' || str[i - 1] == '>')
		&& (str[i] == '|' || str[i + 1] == '|'))
		return (set_status(data, 2, "syntax error near `|'", NULL), 0);
	else if (str[i] == '<' && str[i - 1] == '>')
		return (set_status(data, 2, "syntax error near `<'", NULL), 0);
	else if (str[i] == '>' && str[i - 1] == '<')
		return (set_status(data, 2, "C. syntax error near `\\n'", NULL), 0);
	else if (str[i] == str[i - 1] && is_token(str, (i + 1)))
		return (set_status(data, 2, "D. syntax error near `\\n'", NULL), 0);
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
	if (ft_isprint(c))
		return (1);
	return (0);
}

void	extract_redir_cmds(char **splitted, t_data *data)
{
	int		count;
	int		j;

	j = get_double_tab_len(splitted);
	count = cmd_counter(splitted);
	printf("%i\n", count);
	data->i = 0;
	data->n = 0;
	data->redir_tab = malloc(sizeof(char *) * (count + 1));
	if (!data->redir_tab)
		return ((void)ft_split_free(splitted));
	while (splitted[data->n])
	{
		if (data->n < j && (splitted[data->n][0] == '<'
			|| splitted[data->n][0] == '>'))
			data->n += 2;
		if (data->n < j && splitted[data->n][0] == '|')
			data->n++;
		if (data->n < j && splitted[data->n][0] != '<'
			&& splitted[data->n][0] != '>' && splitted[data->n][0] != '|')
			extract_redir_cmd_finalizer(data, splitted);
	}
	data->redir_tab[data->i] = NULL;
	data->n = 0;
	data->i = 0;
	ft_split_free(splitted);
}

void	extract_redir_cmd_finalizer(t_data *data, char **splitted)
{
	char	*tmp;

	data->redir_tab[data->i] = ft_strdup(splitted[data->n]);
	if (splitted[data->n + 1] && (splitted[data->n + 1][0] != '<'
		&& splitted[data->n + 1][0] != '>' && splitted[data->n + 1][0] != '|'))
	{
		tmp = data->redir_tab[data->i];
		data->redir_tab[data->i] = ft_strjoin(data->redir_tab[data->i], " ");
		free(tmp);
		tmp = data->redir_tab[data->i];
		data->redir_tab[data->i] = ft_strjoin(data->redir_tab[data->i],
				splitted[data->n + 1]);
		free(tmp);
		data->n += 2;
		data->i++;
	}
	else
	{
		data->i++;
		data->n++;
	}
}
