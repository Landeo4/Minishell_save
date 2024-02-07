/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_master.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:48:29 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/05 13:03:10 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_echo(t_data *data)
{
	char	*to_print;
	char	*tmp;
	int		flag;
	(void)flag;

	to_print = export_extract_arg(data->input);
	if (!to_print)
		return (ft_putstr("\n"));
	if (ft_strnstr(to_print, "-n", 2))
	{
		flag = flag_skipper(to_print);
		tmp = ft_substr(to_print, flag, ft_strlen(to_print));
		free(to_print);
		to_print = tmp;
		ft_putstr_fd(to_print, 1);
	}
	else
	{
		ft_putstr_fd(to_print, 1);
		ft_putchar('\n');
	}
	free(to_print);
}

int	is_wspace_or_null(char *str, int i)
{
	if (ft_is_whitespace(str[i]) || !str[i])
		return (1);
	else
		return (0);
}

int	flag_skipper(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] == '-')
			break ;
	while (str[i])
	{
		if (str[i] == '-')
			i++;
		else
			break ;
		if (str[i] != 'n')
			break ;
		while (str[i] && str[i] == 'n')
			i++;
		if (!ft_is_whitespace(str[i]))
			break ;
		else
			while (str[i] && ft_is_whitespace(str[i]))
				i++;
	}
	return (i);
}
