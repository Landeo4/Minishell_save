/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_overall.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 12:26:54 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/22 19:47:18 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// il me faut le argv argv et envp

// int pipe_command(t_data *data)
// {
// 	(void)data;
// 	// printf("%s\n%s\n%s\n", data->cmds[0], data->cmds[1], data->cmds[2]);
//     // printf("input %s\ncounter %d\n", data->input, data->n_args);
//     // printf("c args %d\n", data->c_args);
//     // printf("voici la liste dans data\n");
//     printf("salut\n");
// 	// multi_pipe(data);
// 	// printf("input entier : %s\n", data->input);
// 	// if (data->n_args == 1)
// 		// exec_one_arg(data->input);
// 	// printf("BREF\n");

// 	return (0);
// }

// int multi_pipe(t_data *data)
// {
// 	(void)data;
// 	// file[0] = ft_create_fd(argv[1], O_RDONLY);
// 	// file[1] = ft_create_fd(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC);
// 	// if (file[0] == -1 || file[1] == -1)
// 	// 	return (1);
// 	// ft_pipex(data->cmds, data->envp, data->n_cmds);
// 	return (0);
// }

// // int	ft_pipex(char *argv[], char *env[], int argc)
// // {
// // 	int	i;

// // 	i = 1;
// // 	// dup2(STDIN, 0);
// // 	// dup2(STDOUT, 1);
// // 	process(argv[0], env);
// // 	while (i < argc)
// // 	{
// // 		process(argv[i], env);
// // 		i++;
// // 	}
// // 	ft_do_process(env, argv[i]);
// // 	return (0);
// // }

// // int	process(char *cmd, char *env[])
// // {
// // 	pid_t	pid;
// // 	int		pipefd[2];

// // 	pipe(pipefd);
// // 	pid = fork();
// // 	if (pid)
// // 	{
// // 		close(pipefd[1]);
// // 		dup2(pipefd[0], 0);
// // 		waitpid(pid, NULL, 0);
// // 	}
// // 	else
// // 	{
// // 		close(pipefd[0]);
// // 		dup2(pipefd[1], 1);
// // 		ft_do_process(env, cmd);
// // 	}
// // 	return (0);
// // }

// // void	exec_one_arg(char **cmd)
// // {
// // 	pid_t	pid;
// // 	int		status;

// // 	status = 0;
// // 	pid = 0;
// // 	pid = fork();
// // 	if (pid == -1)
// // 		perror("fork");
// // 	else if (pid > 0)
// // 	{
// // 		waitpid(pid, &status, 0);
// // 		kill(pid, SIGTERM);
// // 	}
// // 	else
// // 	{
// // 		if (execve(cmd[0], cmd, NULL) == -1)
// // 			perror("shell");
// // 		exit(EXIT_FAILURE);
// // 	}
// // }
