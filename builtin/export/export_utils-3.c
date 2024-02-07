/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils-3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsozonof <vsozonof@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 04:12:21 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/29 06:27:03 by vsozonof         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	export_error_handler(char *str, char *to_check, char *rest)
{
	int		i;

	i = 0;
	rest = ft_strdup(str);
	free(str);
	while (rest[i])
	{
		while (!ft_is_whitespace(rest[i]) && rest[i])
			i++;
		to_check = ft_substr(rest, 0, i);
		if (!is_valid_var_name(to_check))
			return (printf(
					"minishell: export:`%s': is not a valid identifier\n",
					to_check), free(to_check), free(rest));
		else
		{
			free(to_check);
			while (ft_is_whitespace(rest[i]) && rest[i])
				i++;
			str = ft_substr(rest, i, (ft_strlen(rest) - i));
			free(rest);
			rest = str;
			i = 0;
		}
	}
}
