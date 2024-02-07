/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_pp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:10:29 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/06 16:50:14 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_dup(int pipe, int token, int pipe2, t_data *data)
{
	(void)data;
	fprintf(stderr, "mon token est donc %d\n", token);
	if (token == 0)
	{
		if (dup2(0, 0) < 0)
			return (printf("problem with dup2 1"), -1);
		if (dup2(pipe2, 1) < 0)
			return (printf("problem with dup2 2"), -1);
	}
	else if (token == 1)
	{
		if (dup2(pipe, 0) < 0)
			return (printf("problem with dup2 3"), -1);
		if (dup2(1, 1) < 0)
			return (printf("problem with dup2 4"), -1);
	}
	else if (token == 2)
	{
		if (dup2(pipe, 0) < 0)
			return (printf("problem with dup2 5"), -1);
		if (dup2(pipe2, 1) < 0)
			return (printf("problem with dup2 6"), -1);
	}
	return (0);
}

// regler le probleme des fd
int	child_process_in(int **pipefd, t_data *data, int i, int token)
{
	char		*buf;

	if (i == 0 || i == data->n_cmds -1)
	{
		if (child_process_in_or_out(pipefd, data, i, token) == -1)
			return (-1);
	}
	else if (token == 0 || token == 1)
	{
		if (child_process_middle(pipefd, data, token) == -1)
			return (-1);
	}
	data->nb_redirs_ac = get_nb_redirs_ac(data->cmds[i]);
	if (check_redirection_now(data, i) == 0)
		redirection_manager(data, i); // !!!! regler les cas ou ca echoue
	buf = arg(data->cmds[i], data);
	free(pipefd[0]);
	free(pipefd[1]);
	return (0);
}

// if (redirection_manager(pipefd, token, data, i) == -1)
// 	return (NULL);

int	child_process_in_or_out(int	**pi, t_data *data, int i, int token)
{
	int	verif;

	if (i == 0)
	{
		close(pi[0][0]);
		close(pi[1][0]);
		close(pi[1][1]);
		if (check_dup(0, 0, pi[0][1], data) == -1)
			return (close(pi[0][1]), free_all_pipe(pi), -1);
		close(pi[0][1]);
	}
	else if (i == data->n_cmds - 1)
	{
		close(pi[1][1]);
		close(pi[0][1]);
		if (token == 0)
			verif = check_dup(pi[1][0], 1, 0, data);
		else
			verif = check_dup(pi[0][0], 1, 0, data);
		close(pi[1][0]);
		close(pi[0][0]);
		if (verif == -1)
			return (free_all_pipe(pi), -1);
	}
	return (0);
}

int	child_process_middle(int **pipefd, t_data *data, int token)
{
	int		verif;

	if (token == 0)
	{
		close(pipefd[1][1]);
		close(pipefd[0][0]);
		verif = check_dup(pipefd[1][0], 2, pipefd[0][1], data);
		close(pipefd[1][0]);
		close(pipefd[0][1]);
		if (verif == -1)
			return (free_all_pipe(pipefd), -1);
	}
	else if (token == 1)
	{
		close(pipefd[0][1]);
		close(pipefd[1][0]);
		verif = check_dup(pipefd[0][0], 2, pipefd[1][1], data);
		close(pipefd[0][0]);
		close(pipefd[1][1]);
		if (verif == -1)
			return (free_all_pipe(pipefd), -1);
	}
	return (0);
}

char	*arg(char *str, t_data *data)
{
	char	**buf;
	int		i;
	char	*tmp;

	tmp = NULL;
	i = ft_strlen(str);
	buf = ft_split(str, ' ');
	if (data->n_redirs > 0)
	{
		if (data->tab[data->index_redirs])
		{
			if (data->tab[data->index_redirs][0] == i)
				return (arg_helper(buf, tmp, data, i));
		}
	}
	tmp = copy_arg(tmp, buf[0]);
	ft_freedb(buf);
	return (tmp);
}

/*
char	*arg(char *str, t_data *data)
{
	char	**buf;
	char	*tmp;
	int		i;
	int		j;

	j = 0;
	tmp = NULL;
	i = ft_strlen(str);
	buf = ft_split(str, ' ');
	if (data->n_redirs > 0)
	{
		if (data->tab[data->index_redirs])
		{
			if (data->tab[data->index_redirs][0] == i)
			{
				if (data->tab[data->index_redirs][1] == 1)
				{
					while (buf[1][j])
					{
						tmp[j] = buf[1][j];
						j++;
					}
					free(buf);
					return (tmp);
				}
				else if (data->tab[data->index_redirs][1] == 3)
				{
					i--;
					while (buf[1][j])
					{
						tmp[j] = buf[i][j];
						j++;
					}
					free(buf);
					return (tmp);
				}
			}
		}
	}
	fprintf(stderr, "%s\n", buf[0]);
	while (buf[0][j])
	{
		tmp[j] = buf[0][j];
		j++;
	}
	j = 0;
	while (buf[j])
	{
		free()
	}
	free(buf);
	return (tmp);
}
*/

/*
char	*arg(char *str, t_data *data)
{
	char	**buf;
	char	*tmp;
	int		i;

	i = ft_strlen(str);
	buf = ft_split(str, ' ');
	tmp = NULL;
	if (data->n_redirs > 0)
	{
		if (data->tab[data->index_redirs])
		{
			if (data->tab[data->index_redirs][0] == i)
			{
				if (data->tab[data->index_redirs][1] == 1)
					ft_copy_tmp(tmp, buf[0]);
				else if (data->tab[data->index_redirs][1] == 3)
					ft_copy_tmp(tmp, buf[i--]);
				free(buf);
				return (tmp);
			}
		}
	}
	tmp = ft_copy_tmp(tmp, buf[0]);
	free(buf);
	return (buf[0]);
}

char	*ft_copy_tmp(char *tmp, char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		tmp[i] = buf[i];
		i++;
	}
	return (tmp);
}
*/