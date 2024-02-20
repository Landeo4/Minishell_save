/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_pp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/22 13:10:50 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/20 14:48:04 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// cat > test1 > test2 < test3 | wc
// ls > out > out1 > out2 < Makefile | cat < Makefile
// cat > test1 > test2 < test3 | wc > test4 < test5 | wc > test6
// donc la mon probleme est que a ma deuxieme boucle, mon fd est a la pos 0
// donc il est detecter comme etant au meme endroit que le reste
// pour la cmd au dessus, il faut que dans out2 il y est un ls
// et que dans mon terminal il y ait le cat makefile
// peut etre ls ecrit proprement  dans out2 mais que tout se fait concatener
// par cat < makefile qui ecrit le makefile dans out2
// si plsuieurs pipe faire attention au input a la place du pipe

// !!! dans redirection manager j'ai baisser mon nb_redirs -> retirer

/*
**	This function takes as parameter: 
**
**
** =====================================================
** =====================================================
**
**
*/

/*
**	This function takes as parameter: 
**
**	data -> the struct who contains all variables
**  to exec our program
**
** =====================================================
** =====================================================
**
**  Pipex_exec will check if we can execute the command
**  with the function ft_do_process (we also get the path)
**  then we go to ft_pipex to start the execution
*/
// pour les commande non valide, mettre u flag dans un tableau qui dit si elles sont executable
int	pipex_exec(t_data	*data)
{
	int		i;
	char	**cmd_argument;

	cmd_argument = NULL;
	data->index_redirs = ((i = 0));
	fprintf(stderr, "je passe par multi\n");
	i = 0;
	if (ft_check_access(data, i) == -1)
		return (free_all_fd(data), 0);
	if (data->n_redirs > 0)
		if (set_first_end(data) == -1)
			return (fprintf(stderr, "problem with malloc\n"), -1);
	ft_pipex(data, i, cmd_argument);
	ft_freedb(data->actual_path);
	if (data->n_redirs > 0)
	{
		free(data->first);
		free(data->last);
	}
	return (0);
}

int	ft_check_access(t_data *data, int i)
{
	char	*buf;

	buf = NULL;
	data->actual_path = malloc(sizeof(char *) * (len_db_tab(data->cmds) + 1));
	if (!data->actual_path)
		return (-1);
	while (data->cmds[i])
	{
		buf = arg(data->cmds[i], data);
		fprintf(stderr, "voici buf %s et voici cmds %s\n", buf, data->cmds[i]);
		if (!data->pr->nv)
			return (fprintf(stderr, "problem with env\n"), -1);
		data->actual_path[i] = ft_do_process(data->pr->nv, buf);
		if (!data->actual_path[i])
			data->cmd_valid[i] = -1;
		free(buf);
		i++;
	}
	data->actual_path[i] = NULL;
	return (0);
}

/*
**	This function takes as parameter:
**
**	data = the structure
**
** =====================================================
** =====================================================
**
**	this function set the first redirection and the
**	final of each pipe
**
*/

int	set_first_end(t_data *data)
{
	int		i;
	int		j;
	int		count;

	i = ((count = 0));
	data->first = malloc(sizeof(int) * data->n_redirs);
	data->last = malloc(sizeof(int) * data->n_redirs);
	if (!data->first || !data->last)
		return (-1);
	data->index_fd = -1;
	j = 0;
	while (data->cmds[i])
	{
		if (i > 0)
			count = get_act_redir(data, i);
		if (check_if_redir(data, i) == 0)
		{
			data->first[j] = first_redirect(data, data->cmds[i], count);
			data->last[j] = last_redirect(data, data->cmds[i], count);
			j++;
		}
		i++;
	}
	return (0);
}

// peut etre modifier la fonction en dessous
// j'essaye de regler si il n'y a pas de redirection
// dans un pipe
int	check_if_redir(t_data *data, int i)
{
	int		j;

	j = 0;
	while (data->cmds[i][j])
	{
		// if (is_in_quotes(data->cmds[i], j) > 0)
		// {
		if (data->cmds[i][j] == '>'
		|| data->cmds[i][j] == '<')
			return (0);
		// }
		j++;
	}
	return (-1);
}

int	get_act_redir(t_data *data, int i)
{
	int		count;
	int		j;
	int		c;

	j = ((c = 0));
	count = 0;
	if (c < i)
	{
		while (c < i)
		{
			j = 0;
			while (data->cmds[c][j])
			{
				if ((data->cmds[c][j] == '>'
				|| data->cmds[c][j] == '<')
				&& (data->cmds[c][j + 1] != '>'
				|| data->cmds[c][j + 1] != '<'))
					count++;
				j++;
			}
			c++;
		}
	}
	return (count);
}

/*
data->actual_path = malloc(sizeof(char *) * (len_db_tab(data->cmds) + 1));
	if (!data->actual_path)
		return (0);
	while (data->cmds[i])
	{
		data->actual_path[i] = malloc(sizeof(char) * (ft_strlen(data->cmds[i]) + 1));
		if (!data->actual_path[i])
			return (0);
		buf = arg(data->cmds[i], data);
		data->actual_path[i] = ft_do_process(data->pr->nv, buf);
		if (!data->actual_path[i])
		{
			perror("wrong commd\n");
			free(buf);
			// ft_freedb(data->cmds);
			return (0);
		}
		free(buf);
		i++;
	}
*/

/* acien ft_check_access
int	ft_check_access(t_data *data, int i)
{
	char	*buf;
	int		j;

	j = 0;
	data->actual_path = malloc(sizeof(char *) * len_db_tab(data->cmds));
	if (!data->actual_path)
		return (-1);
	while (data->cmds[i])
	{
		data->actual_path[i] = malloc(sizeof(char) * (ft_strlen(data->cmds[i]) + 1));
		if (!data->actual_path[i])
		{
			fprintf(stderr, "access a echouer\n");
			while (i >= 0)
				free(data->actual_path[i--]);
			free(data->actual_path);
			data->actual_path = NULL;
			return (-1);
		}
		buf = arg(data->cmds[i], data);
		data->actual_path[i] = ft_do_process(data->pr->nv, buf);
		if (!data->actual_path[i])
		{
			perror("wrong commd\n");
			free(buf);
			return (-1);
		}
		data->actual_path[i][ft_strlen(data->cmds[i]) + 1] = '\0';
		free(buf);
		i++;
	}
	fprintf(stderr, "access a reussis\n");
	return (0);
}
*/

/*
data->actual_path = malloc(sizeof(char *) * (len_db_tab(data->cmds) + 1));
	if (!data->actual_path)
		return (0);
	while (data->cmds[i])
	{
		data->actual_path[i] = malloc(sizeof(char) * ft_strlen(data->cmds[i]));
		if (!data->actual_path[i])
			return (0);
		buf = arg(data->cmds[i], data);
		data->actual_path[i] = ft_do_process(data->pr->nv, buf);
		if (!data->actual_path[i])
		{
			while (i > 0)
				free(data->actual_path[i--]);
			free(data->actual_path);
			perror("wrong commd\n");
			free(buf);
			// ft_freedb(data->cmds);
			return (0);
		}
		free(buf);
		i++;
	}
	data->actual_path[i] = NULL;
*/