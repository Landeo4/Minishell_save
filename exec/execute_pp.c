/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:31:19 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/20 14:20:35 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_do_process(char *envp[], char *cmd)
{
	int		i;
	char	**path;
	char	*buf2;

	i = 0;
	if (ft_do_process_helper(cmd) == 0)
	{
		buf2 = ft_strdup(cmd);
		return (buf2);
	}
	path = ft_get_path(envp);
	if (!path)
		return (NULL);
	if (!path)
		return (NULL);
	while (path[i++])
	{
		buf2 = ft_strjoin_help(path, cmd, i);
		if (access(buf2, X_OK) == 0)
		{
			ft_split_free(path);
			return (buf2);
		}
		free(buf2);
	}
	ft_split_free(path);
	return (NULL);
}

int	ft_do_process_helper(char *cmd)
{
	if (access(cmd, X_OK) == 0)
	{
		// data->status->code[];
		return (0);
	}
	// data->
	return (-1);
}

char	*ft_strjoin_help(char **path, char *cmd, int i)
{
	char	*buf;
	char	*buf2;

	buf = ft_strjoin(path[i], "/");
	if (!buf)
		return (fprintf(stderr, "ERROR IN PATH\n"), NULL);
	buf2 = ft_strjoin(buf, cmd);
	if (!buf2)
		return (fprintf(stderr, "ERROR IN PATH\n"), NULL);
	free(buf);
	return (buf2);
}

char	**ft_get_path(char **env)
{
	int		i;
	char	**path;

	i = 0;
	while (ft_strncmp(env[i], "PATH=", 5) != 0)
	{
		if (!env[i + 1])
			break;
		i++;
	}
	if (!env[i])
		perror("Error: PATH not found");
	path = ft_split(env[i] + 5, ':');
	return (path);
}
