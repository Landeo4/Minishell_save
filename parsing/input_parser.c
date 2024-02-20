/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:14:23 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/20 13:26:41 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// * Input basique trouvable dans data.input
// * Flags et Args trouvable dans data.arg / data.flag
// * Env trouvable dans data.envp

// void	input_parser(t_prompt *pr, t_data *data)
// {
// 	if (!input_to_lst(pr, data))
// 		return (free_master(data));
// 	ft_printlst(data->inp);
// 	free_master(data);
	
// }

int	input_to_lst(t_prompt *pr, t_data *data)
{
	int		i;
	char	**tab;

	i = 0;
	init_str(data, pr);
	tab = malloc(sizeof(char *) * (lexer_counter(data->input) + 1));
	if (!tab)
		return (0);
	while (data->input)
	{
		tab[i] = input_splitter(data);
		i++;
		if (ft_strlen(data->input) == 0)
		{
			if (data->input)
				free(data->input);
			data->input = NULL;
		}
	}
	tab[i] = NULL;
	if (!put_input_to_lst(data->inp, tab))
		return (0);
	return (1);
}

char	*input_splitter(t_data *data)
{
	int		i;
	int		c;
	char	*tmp;
	char	*ret;

	i = 0;
	while (data->input[i] && !is_in_quotes(data->input, i)
		&& ft_is_whitespace(data->input[i]))
		i++;
	c = get_next_split(data->input, i);
	tmp = ft_substr(data->input, c, ft_strlen(data->input));
	if (!tmp)
		return (NULL);
	ret = ft_substr(data->input, i, (c - i));
	if (!ret)
		return (NULL);
	free(data->input);
	data->input = tmp;
	return (ret);
}

int	get_next_split(char *str, int i)
{
	int	c;

	c = i;
	if (str[c] == 39 || str[c] == '"')
		c += (quote_skipper(str, c) - c);
	else if (token_identifier(str, c))
		c += token_identifier(str, c);
	else
	{
		while (str[c] && !ft_is_whitespace(str[c]))
		{
			if (!is_special_char(str[c]))
				break ;
			c++;
		}
	}
	return (c);
}

int	put_input_to_lst(t_input *ptr, char **tab)
{
	int		i;
	t_input	*nav;

	i = 0;
	if (!tab)
		return (0);
	nav = ptr;
	while (tab[i])
	{
		nav->str = ft_strdup(tab[i]);
		if (tab[i + 1])
		{
			nav->next = malloc(sizeof(t_input));
			if (!nav->next)
				return (0);
			nav = nav->next;
		}
		else
			nav->next = NULL;
		i++;
	}
	ft_split_free(tab);
	return (1);
}

int	is_special_char(char c)
{
	if (c == 39 || c == '"' || c == '>' || c == '<')
		return (0);
	return (1);
}


void	input_parser(t_prompt *prompt, t_data *data)
{
	init_str(data, prompt);
	if (!is_piped_input_valid(prompt->input, data))
		return (free_manager(data, 0));
	if (is_there_pipe(prompt))
	{
		data->cmds = pipes_splitter(prompt->input, '|', data);
		if (!data->cmds)
			return (set_status(data, 12, "malloc error.", NULL),
				free_manager(data, 0));
	}
	if (!redirection_and_expand_handler(data))
		return (free_manager(data, 0));
	if (is_there_pipe(prompt))
	{
		command_manager(data);
		free_manager(data, 2);
	}
	else if (!is_there_pipe(prompt))
	{
		if (!get_cmd(data))
			return (free_manager(data, 0));
		command_manager(data);
		free_manager(data, 1);
	}
}

int	get_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (data->input[i] && ft_is_whitespace(data->input[i]))
		i++;
	data->input = ft_substr(data->pr->input, i, ft_strlen(data->pr->input));
	if (!data->input)
		return (set_status(data, 12, "malloc error.", NULL), 0);
	return (data->n_cmds = 1, 1);
}
