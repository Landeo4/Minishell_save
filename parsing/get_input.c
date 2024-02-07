/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 13:42:18 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/30 11:01:37 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_input(char **envp)
{
	t_prompt	prompt;

	init_sbase(&prompt, envp);
	init_extras(&prompt);
	while (42)
	{
		printf("%s at %s in: %s", prompt.user, prompt.post, prompt.w_d);
		prompt.input = readline("\n$> ");
		if (prompt.input)
		{
			add_history(prompt.input);
			if (!is_input_valid(prompt.input))
				free(prompt.input);
			else
				input_parser(&prompt);
		}
		else
			break ;
	}
	clear_history();
	free_end_of_program(&prompt);
}
