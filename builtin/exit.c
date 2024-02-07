/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 17:52:12 by tpotilli          #+#    #+#             */
/*   Updated: 2024/01/30 04:36:34 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_exit(t_data *data)
{
	printf("Exit Shell\n");
	(void)data;
	// free_data_struct(data);
	return (0);
}
