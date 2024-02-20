/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:52:12 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/20 11:20:03 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

long long int	ft_atoll_1(const char *str)
{
	long long int	var;
	int				i;
	int				sign;

	i = 0;
	sign = 1;
	var = 0;
	if (!(str))
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		var = (var * 10) + (str[i] - '0');
		i++;
	}
	return (var * sign);
}

int	status_checker(char	*input, t_data *data)
{
	char		*status;
	long int	i_status;
	int			i;

	i = -1;
	status = export_extract_arg(input);
	if (!status)
		return (set_status(data, 12, "malloc error.", NULL), -1);
	if (status[0] == '-' || status[0] == '+')
		i++;
	while (status[++i])
		if (!ft_isdigit(status[i]))
			return (free(status), set_status(data, 2,
					"numeric argument required", "exit"), 2);
	if (!ft_int_overflow_checker(status))
		return (free(status), set_status(data, 2,
				"numeric argument required", "exit"), 2);
	i_status = ft_atoll_1(status);
	if (i_status < 0 || i_status > 255)
		i_status = (i_status % 256 + 256) % 256;
	free(status);
	return (i_status);
}

void	execute_exit(t_data *data)
{
	int	status;

	data->input = quote_remover_v2(data->input);
	printf("exit\n");
	if (n_args(data->input) == 0)
		data->exited = 1;
	else if (n_args(data->input) == 1)
	{
		status = status_checker(data->input, data);
		set_status(data, status, NULL, NULL);
		data->exited = 1;
	}
	else
	{
		set_status(data, 1, "too many arguments", "exit");
		data->exited = 1;
	}
}
