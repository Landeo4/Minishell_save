/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_redirection_case.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 00:15:46 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/27 00:31:05 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	redirection_case_1(int fd, t_data *data, int **pipefd)
// {
// 	fd = data->tab[data->index_redirs][1];
// 	//check si: int out middle
// 	if (data->i == 0)
// 	{
// 		if (check_dup(fd, 2, pipefd[][], data) == -1) // trouver quel pipefd mettre
// 			return (free_pipe_argv(pipefd, data->cmds), -1);
// 		// close(pipefd[0][0]);
// 		// close(pipefd[0][1]);
// 		// close(pipefd[1][0]);
// 		// close(pipefd[1][1]);
// 		return (0);
// 	}
// 	else if (data->i == data->n_cmds - 1)
// 	{
// 		if (check_dup(fd, 1, 1, data) == -1) // trouver quel pipefd mettre
// 			return (free_pipe_argv(pipefd, data->cmds), -1);
// 		close(pipefd[0][0]);
// 		close(pipefd[0][1]);
// 		close(pipefd[1][0]);
// 		close(pipefd[1][1]);
// 		return (0);
// 	}
// 	return (0);
// }

// int	redirection_case_2(int fd, int fd2, t_data *data, int **pipefd)
// {
// 	fd2 = data->tab[data->index_redirs + 1][1];
// //check si: int out middle
// 	if (data->i == 0)
// 	{
// 		if (check_dup(0, 2, fd2, data) == -1) // trouver quel pipefd mettre
// 			return (free_pipe_argv(pipefd, data->cmds), -1);
// 		// close(pipefd[0][0]);
// 		// close(pipefd[0][1]);
// 		// close(pipefd[1][0]);
// 		// close(pipefd[1][1]);
// 		return (0);
// 	}
// 	else if (data->i == data->n_cmds - 1)
// 	{
// 		if (check_dup(pipefd[][], 1, fd2, data) == -1) // trouver quel pipefd mettre
// 			return (free_pipe_argv(pipefd, data->cmds), -1);
// 		close(pipefd[0][0]);
// 		close(pipefd[0][1]);
// 		close(pipefd[1][0]);
// 		close(pipefd[1][1]);
// 		return (0);
// 	}
// 	return (0);
// }

// int	redirection_case_3(int fd, int fd2, t_data *data, int **pipefd)
// {
// 	fd = data->tab[data->index_redirs][1];
// 	fd2 = data->tab[data->index_redirs + 1][1];
// 	//check si: int out middle
// 	if (check_dup(fd, 2, fd2) == -1) // trouver quel pipefd mettre
// 		return (-1);
// }
