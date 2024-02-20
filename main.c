/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 23:29:44 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/19 14:22:17 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// valgrind --leak-check=full --suppressions=rl_leak_ignore.supp ./minishell
int	g_status;

void	init_vars(t_prompt *ptr)
{
	ptr->user = NULL;
	ptr->w_d = NULL;
	ptr->post = NULL;
	ptr->env = NULL;
	ptr->name = NULL;
	ptr->pid = NULL;
	ptr->nv = NULL;
	ptr->data->c_status = NULL;
	ptr->data->i_status = 0;
}

int	main(int argc, char **argv, char *envp[])
{
	t_prompt	prompt;
	t_data		data;

	(void)argc;
	(void)argv;
	prompt.data = &data;
	init_vars(&prompt);
	if (!init_sbase(&prompt, envp) || !init_extras(&prompt))
	{
		free_end_of_program(&prompt);
		return (data.i_status);
	}
	return (get_input(&prompt, &data));
}
