/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_master.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:54:08 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/30 02:44:13 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_unset(t_data *data)
{
	int		i;
	char	*args;
	char	**splitted;

	i = 0;
	args = export_extract_arg(data->input);
	splitted = ft_split(args, ' ');
	while (splitted[i])
	{
		do_unset(splitted[i], data);
		i++;
	}
	ft_split_free(splitted);
	free(args);
}

void	do_unset(char *args, t_data *data)
{
	if (!ft_get_env_node(data->env, args))
		return ;
	else
		del_var_from_env(data, args);
}
