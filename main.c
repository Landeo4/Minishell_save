/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:29:44 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/05 10:53:35 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// valgrind --leak-check=full --suppressions=rl_leak_ignore.supp ./minishell
int	g_status;

int	main(int argc, char **argv, char *envp[])
{
	(void)argc;
	(void)argv;
	get_input(envp);
}
