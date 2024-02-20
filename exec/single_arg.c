/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 18:55:02 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/20 13:52:53 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	single_arg(t_data *data, char **cmd_argument)
{
	char	*buf;
	char	*fre;
	char	*essaie;
	int		check;

	if (builtin_single(data) == -1)
		return (-1);
	buf = arg(data->input, data);
	if (!buf)
		return (-1);
	if (data->n_redirs > 0)
		essaie = ft_strdup(data->redir_tab[0]);
	else
		essaie = data->input;
	fre = ft_do_process(data->pr->nv, buf);
	if (!fre)
		return (free(buf), -1);
	free(buf);
	cmd_argument = ft_split(essaie, ' ');
	if (cmd_argument == NULL)
		return (free(buf), -1);
	check = check_fre_cmd(data, buf, cmd_argument, fre);
	if (check == 1)
		return (-1);
	exec_single(cmd_argument, fre, data);
	if (data->n_redirs > 0)
		free(essaie);
	free_single(data, cmd_argument, fre);
	printf("mon programme se finis donc normalement\n");
	return (0);
}

int	builtin_single(t_data *data)
{
	int	check;
	int	du1;
	int	du2;

	check = builtin_checker(data->input);
	fprintf(stderr, "MON NOMBRE DE REIDRCTION %d\n", data->n_redirs);
	if (check >= 1 && check <= 7)
	{
		fprintf(stderr, "donc voici mon nb de redirs au debut %d\n", data->n_redirs);
		if (data->n_redirs > 0)
		{
			du1 = dup(0);
			du2 = dup(1);
			data->first = malloc(sizeof(int) * 1);
			data->last = malloc(sizeof(int) * 1);
			fprintf(stderr, "avant les NULL\n");
			if (!data->first || !data->last)
			{
				close_all_redirs(data);
				dup2(du1, 0);
				dup2(du2, 1);
				close(du1);
				close(du2);
				free(data->first);
				free(data->last);
				return (-1);
			}
			fprintf(stderr, "apres les NULL\n");
			data->first[0] = first_redirect(data, data->input, 0);
			data->last[0] = last_redirect(data, data->input, 0);
			redirection_dup1_in(data, data->first[0], data->last[0]);
		}
		builtin_manager(data, check);
		fprintf(stderr, "donc voici mon nb de redirs %d\n", data->n_redirs);
		if (data->n_redirs > 0)
		{
			close_all_redirs(data);
			dup2(du1, 0);
			dup2(du2, 1);
			close(du1);
			close(du2);
			free(data->first);
			free(data->last);
		}
		return (-1);
	}
	return (0);
}

int	check_fre_cmd(t_data *data, char *buf, char **cmd_argument, char *fre)
{
	if (!fre || !cmd_argument)
	{
		set_status(data, 1, "command not found", buf);
		free(buf);
		ft_freedb(cmd_argument);
		return (1);
	}
	return (0);
}

int	exec_single(char **cmd_argument, char *fre, t_data	*data)
{
	int		pid;
	// int		x;

	// x = 0;
	pid = fork();
	if (pid < 0)
		return (printf("error in fork\n"), -1);
	else if (pid == 0)
	{
		if (data->n_redirs > 0)
		{
			if (redirection_single(data) == -1)
				return (-1);
		}
		execve(fre, cmd_argument, data->pr->nv);
		free(fre);
		ft_freedb(cmd_argument);
		exit(0);
	}
	else if (pid > 0)
		waitpid(pid, NULL, 0);
	return (0);
}

int	redirection_single(t_data *data)
{
	int		last;
	int		first;
	// int		i;

	heredoc_counter(data);
	if (data->nb_here_doc > 0)
		main_here_doc(data);
	first = first_redirect(data, data->input, 0);
	last = last_redirect(data, data->input, 0);
	// i = 0;
	if (data->n_redirs >= 1)
	{
		if (redirection_dup1_in(data, first, last) == -1)
			return (-1);
	}
	return (0);
}

int	redirection_single_chev(t_data *data, char *input)
{
	int		i;
	int		cpt;

	i = 0;
	cpt = data->tab[0][0];
	while (input[i++])
	{
		if (input[i] == ' ')
			cpt--;
		if (input[i] == '>' && cpt > 0)
			return (1);
		else if (input[i] == '<' && cpt > 0)
			return (2);
		else if ((input[i] == '>' || input[i] == '<')
			&& cpt == 0)
			return (0);
	}
	return (-1);
}
