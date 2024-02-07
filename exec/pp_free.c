/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pp_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:12:21 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/06 16:48:57 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*str_join_free(char *path, char *cmd)
{
	char	*str;

	str = ft_strjoin(path, cmd);
	free(path);
	return (str);
}

void	ft_freedb(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_all_pipe(int **pipefd)
{
	close(pipefd[0][0]);
	close(pipefd[0][1]);
	close(pipefd[1][1]);
	close(pipefd[1][0]);
	free(pipefd[1]);
	free(pipefd[0]);
	free(pipefd);
}

void	free_single(t_data *data, char **cmd_argument, char *buf, char *fre)
{
	int		i;

	i = 0;
	ft_freedb(cmd_argument);
	free(buf);
	free(fre);
	data->index_redirs = 0;
	if (data->n_redirs > 0)
	{
		while (data->n_redirs > 0)
		{
			close(data->tab[i][2]);
			i++;
			data->n_redirs--;
		}
	}
}
