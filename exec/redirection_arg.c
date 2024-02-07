/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 00:18:44 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/01 17:15:06 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *ft_essaie(t_data *data, char *input)
{
	char	*buf;
	char	*buf2;
	int		c;
	int		i;

	i = ((c = 0));
    fprintf(stderr, "voici linput pour la len %s\n", input);
	buf = malloc(sizeof(char) * (ft_strlen(input) + 1));
	fprintf(stderr ,"ma len = %zu\n", ft_strlen(input));
	while (input[i])
	{
		if (input[i] != '>' && input[i] != '<')
		{
			buf[c] = input[i];
			c++;
		}
		i++;
	}
	buf[c] = '\0';
	i = ((c = 0));
	buf2 = ft_essaie_helper(buf, input, c, data);
	free(buf);
	return (buf2);
}

char *ft_essaie_helper(char *buf, char *input, int j, t_data *data)
{
	char	*str;
	int		len;
	int		i;

	i = 0;
    while (data->input[i++])
    {
        if (data->input[i] == '>' || data->input[i] == '<')
        {
            j++;
            if (data->input[i + 1] == '>' || data->input[i + 1] == '<')
            	i++;
        }
    }
	i = (j = 0);
	len = len_buf(buf, input, data, j);
	str = malloc(sizeof(char) * (len + 1));
	while (input[i])
	{
		if (input[i] == ' ' && (input[i + 1] == '>'
		|| input[i + 1] == '<'))
		{
			i += 3;
			while (ft_isalnum(input[i]))
				i++;
			if (!input[i])
				break;
		}
		str[j] = input[i];
		i++;
		j++;
	}
	str[j] = '\0';
	fprintf(stderr, "VOICI LE RESULTAT de ft_essaie_helper %s\n", str);
	return (str);
}

/* Premiere generation qui fonctionne en single arg
char *ft_essaie(t_data *data, char *input)
{
	char	*buf;
	char	*buf2;
	int		c;
	int		i;

	buf = malloc(sizeof(char) * (ft_strlen(input) + 1));
	i = 0;
	c = 0;
	while (input[i])
	{
		if (input[i] != '>' && input[i] != '<')
		{
			buf[c] = input[i];
			c++;
		}
		i++;
	}
	buf[c] = '\0';
	i = 0;
	c = 0;
	buf2 = ft_essaie_helper(buf, i, c, data);
	free(buf);
	return (buf2);
}

char *ft_essaie_helper(char *buf, int i, int j, t_data *data)
{
	char	*str;
	int		len;
	(void)j;
	(void)data;

	len = len_buf(buf, i);
	str = malloc(sizeof(char) * (len + 2));
	while (buf[i])
	{
		if (i == 11)
		{
			i++;
			while (buf[i] != ' ')
				i++;
			i++;
		}
		str[j] = buf[i];
		j++;
		i++;
		// if (buf[i] == ' ' && buf[i + 1] == ' ')
		// 	i++;
	}
	str[j] = '\0';
	fprintf(stderr, "VOICI LE RESULTAT %s\n", str);
	return (str);
}

*/