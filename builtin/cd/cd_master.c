/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_master.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:02:25 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/13 08:10:34 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_cd(t_data *data)
{
	char	*path;

	data->input = quote_remover_v2(data->input);
	if (n_args(data->input) == 0)
	{
		if (!ft_get_env_node(data->env, "HOME"))
			return (set_status(data, 1, "HOME not set.", "cd :"));
		change_directory(data, ft_get_env(data->env, "HOME"));
		return (set_status(data, 0, NULL, NULL));
	}
	else if (n_args(data->input) != 1)
		return (set_status(data, 1, "too many arguments.", "cd :"));
	path = cd_extract_arg(data->input);
	if (!ft_strncmp(path, "..", 2) && path[2] == '\0')
	{
		go_back_one_level(data);
		free(path);
		return (set_status(data, 0, NULL, NULL));
	}
	else
		change_directory(data, path);
}

void	go_back_one_level(t_data *data)
{
	char	*path;
	int		i;

	i = ft_strlen(data->pr->w_d);
	i--;
	while (i > 0 && data->pr->w_d[i] && data->pr->w_d[i] != '/')
		i--;
	path = ft_substr(data->pr->w_d, 0, i + 1);
	change_directory(data, path);
}

void	change_directory(t_data *data, char *path)
{
	if (access(path, F_OK) != -1)
	{
		if (chdir(path) == 0)
		{
			update_vars(data);
			return (free(path));
		}
		else
			error_handling(errno, path, data);
	}
	else
		error_handling(errno, path, data);
}

void	update_vars(t_data *data)
{
	t_env	*pwd;
	t_env	*old_pwd;
	char	*old_wd;

	old_pwd = ft_get_env_node(data->env, "OLDPWD");
	pwd = ft_get_env_node(data->env, "PWD");
	free(data->pr->w_d);
	data->pr->w_d = getcwd(NULL, 0);
	if (pwd && old_pwd)
	{
		old_wd = pwd->var;
		free(old_pwd->var);
		old_pwd->var = ft_strjoin("OLD", old_wd);
		free(old_wd);
		pwd->var = ft_strjoin("PWD=", data->pr->w_d);
	}
}
