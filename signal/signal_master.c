/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_master.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 09:27:48 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/30 11:13:19 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(int signum)
{
	t_prompt	ptr;
	char		*tmp;

	if (signum == SIGINT)
	{
		ptr.user = getenv("LOGNAME");
		tmp = getenv("SESSION_MANAGER");
		ptr.post = ft_substr(tmp, 6, 12);
		ptr.w_d = getcwd(NULL, 0);
		printf("\n%s at %s in: %s\n", ptr.user, ptr.post, ptr.w_d);
		rl_on_new_line();
		rl_replace_line("", 1);
		rl_redisplay();
		free(ptr.post);
	}
	else if (signum == SIGQUIT)
		(void)signum;
}
