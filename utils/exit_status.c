/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 04:46:20 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/30 09:27:08 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_updater(t_data *data, int status, char *str, char *cmd)
{
	printf("minishell: ");
	if (cmd)
		printf("%s:", cmd);
	if (str)
		printf(" %s\n", str);
	free(data->c_status);
	data->i_status = status;
	data->c_status = ft_itoa(status);
}
