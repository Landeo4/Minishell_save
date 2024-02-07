/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_master.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 12:09:39 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/30 02:57:42 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	printf("%s\n", pwd);
	free(pwd);
}
