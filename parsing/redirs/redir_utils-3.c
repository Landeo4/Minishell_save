/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils-3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:49:25 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/20 10:11:49 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*file_name_finder(t_data *data, int i, int c)
{
	i++;
	while (ft_is_whitespace(data->input[i]) && data->input[i])
		i++;
	c = i;
	while (!ft_is_whitespace(data->input[i]) && data->input[i])
		i++;
	return (ft_substr(data->input, c, (i - c)));
}

void	set_tab_values(t_data *data, int n, int i, int mode)
{
	char	*file_name;

	file_name = NULL;
	if (mode == 1)
	{
		if (data->input[i] == '<')
		{
			file_name = file_name_finder(data, i, 0);
			data->tab[n][0] = i;
			data->tab[n][1] = 1;
			data->tab[n][2] = ft_create_fd(file_name,
					O_RDONLY);
		}
		else if (data->input[i] == '>')
		{
			file_name = file_name_finder(data, i, 0);
			data->tab[n][0] = i;
			data->tab[n][1] = 3;
			data->tab[n][2] = ft_create_fd(file_name,
					O_WRONLY | O_CREAT | O_TRUNC);
		}
	}
	else if (mode == 2)
		tab_value_setter_double(data, n, i);
	free(file_name);
}

void	get_redir_infos(t_data *data, int i, int n)
{
	while (data->input[i])
	{
		if (!is_in_quotes(data->input, i)
			&& ((data->input[i] == '<' && data->input[i + 1] != '<')
				|| (data->input[i] == '>' && data->input[i + 1] != '>')))
		{
			if (data->tab[n])
				set_tab_values(data, n, i, 1);
			n++;
			i++;
		}
		else if (!is_in_quotes(data->input, i)
			&& ((data->input[i] == '<' && data->input[i + 1] == '<')
				|| (data->input[i] == '>' && data->input[i + 1] == '>')))
		{
			if (data->tab[n])
				set_tab_values(data, n, i, 2);
			n++;
			i += 2;
		}
		else
			i++;
	}
}

void	tab_value_setter_double(t_data *data, int n, int i)
{
	char	*file_name;

	file_name = NULL;
	if (data->input[i] == '>' && data->input[i + 1] == '>')
	{
		i++;
		file_name = file_name_finder(data, i, 0);
		fprintf(stderr, "file name %s\n", file_name);
		data->tab[n][0] = i;
		data->tab[n][1] = 4;
		data->tab[n][2] = ft_create_fd(file_name,
					O_WRONLY | O_APPEND);
		if (!data->tab[n][2])
			ft_create_fd(file_name, O_WRONLY | O_APPEND);
	}
	else if (data->input[i] == '<' && data->input[i + 1] == '<')
	{
		data->tab[n][0] = i;
		data->tab[n][1] = 2;
		data->tab[n][2] = 0;
	}
	free(file_name);
}

int	are_token_sep_by_wspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '>' || str[i] == '<')
		{
			if ((str[i + 1] == '>' || str[i + 1] == '<')
				&& (ft_is_whitespace(str[i - 1])
					&& ft_is_whitespace(str[i + 2])))
				i += 2;
			else if ((str[i + 1] != '>' || str[i + 1] != '<')
				&& (ft_is_whitespace(str[i - 1])
					&& ft_is_whitespace(str[i + 1])))
				i++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
