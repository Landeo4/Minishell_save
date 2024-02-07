/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/16 05:50:43 by vsozonof          #+#    #+#             */
/*   Updated: 2024/01/26 23:25:00 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_env(t_env *env, char *str)
{
	int		len;
	t_env	*nav;

	nav = env;
	len = ft_strlen(str);
	while (nav)
	{
		if (!ft_strncmp(nav->var, str, len))
			return (ft_substr(nav->var, (len + 1), ft_strlen(nav->var)));
		else
			nav = nav->next;
	}
	return (NULL);
}

t_env	*ft_get_env_node(t_env *env, char *str)
{
	int		len;
	t_env	*nav;

	nav = env;
	len = ft_strlen(str);
	while (nav)
	{
		if (!ft_strncmp(nav->var, str, len))
			return (nav);
		else
			nav = nav->next;
	}
	return (NULL);
}

int	put_env_to_lst(t_env *env, char **envp)
{
	int		i;
	t_env	*nav;

	i = 0;
	if (!envp)
		return (0);
	nav = env;
	while (envp[i])
	{
		nav->var = ft_strdup(envp[i]);
		if (!nav->var)
			return (0);
		if (envp[i + 1])
		{
			nav->next = malloc(sizeof(t_env));
			if (!nav->next)
				return (0);
			nav = nav->next;
		}
		else
			nav->next = NULL;
		i++;
	}
	return (1);
}

void	ft_printlst(t_env *L)
{
	if (L == NULL)
	{
		printf("La liste est vide.\n");
		return ;
	}
	while (L && L->next)
	{
		ft_printf("-> %s\n", L->var);
		L = L->next;
	}
}
