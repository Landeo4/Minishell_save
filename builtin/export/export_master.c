/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:49:13 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/30 00:31:40 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_export(t_data *data)
{
	int		i;
	char	*args;

	i = 0;
	args = export_extract_arg(data->input);
	if (!args)
		return (free(args), export_no_args(data->env));
	else if (!export_valid_args_counter(args))
		return (export_error_handler(args, NULL, NULL));
	else
	{
		while (args[i])
		{
			if (export_is_valid_arg(args, i))
			{
				i = export_is_valid_arg(args, i);
				args = export_finalizer(args, i, data);
				i = 0;
			}
			if ((i + 1) <= (int)ft_strlen(args))
				i++;
		}
	}
	free(args);
}

char	*export_finalizer(char *args, int i, t_data *data)
{
	char		*var_name;
	char		*var_value;
	char		*new_arg;
	static int	flag;

	new_arg = ft_substr(args, i, ft_strlen(args));
	var_name = extract_var_name(args, i);
	if (!is_valid_var_first_char(var_name[0]))
	{
		if (!flag)
		{
			flag += 1;
			printf("minishell: export:`%s': is not a valid identifier\n",
				var_name);
		}
		return (free(var_name), free(args), new_arg);
	}
	var_value = extract_var_value(args, i);
	do_export(var_name, var_value, data);
	free(args);
	return (new_arg);
}

void	do_export(char *var_name, char *var_value, t_data *data)
{
	char	*var;
	t_env	*nav;

	nav = NULL;
	var = ft_strjoin(var_name, "=");
	if (!var_value)
		var_value = ft_strdup("");
	if (is_there_quotes(var_value))
		var_value = quote_remover_v2(var_value);
	var = strjoin_and_free(var, var_value);
	if (!ft_get_env_node(data->env, var_name))
		add_var_to_env(data, var);
	else
	{
		nav = ft_get_env_node(data->env, var_name);
		free(nav->var);
		nav->var = var;
	}
	free(var_name);
}
