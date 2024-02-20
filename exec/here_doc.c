/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 12:45:18 by tpotilli          #+#    #+#             */
/*   Updated: 2024/02/14 15:51:42 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// char	*main_here_doc(t_data *data)
// {
// 	fprintf(stderr, "j'ai detecter un here_doc\n");
// 	while (nb_here_doc > 0)
// 	{
// 		path = ft_do_here_doc(data);
// 		nb_here_doc--;
// 	}
// 	return (path);
// }

// char    *ft_do_here_doc(t_data *data)
// {
// 	char    *path;
// 	char	*file;
// 	char	*flag;
// 	(void)data;

// 	path = NULL;
// 	file = get_name_heredoc();
// 	if (ft_create_fd(file, O_WRONLY | O_CREAT | O_TRUNC))
// 		return (NULL);
// 	flag = get_flag_here(data);
// 	if (ft_make_here_doc(data, file, data->input) == -1)
// 		return (NULL);
// 	return (path);
// }
// // regler ou faire nouveau pour faire en double
// int	ft_make_here_doc(t_data *data, int file, char *input, char *flag)
// {
// 	int		i;
// 	char	**buf;
// 	char	*str;

// 	i = 0;
// 	buf = NULL;
// 	while (input[i] && input[i])
// 	{
// 		buf[i] = get_next_line();
// 		write(file, &buf[i], ft_strlen(buf[i]));
// 		i++;
// 	}
// 	str = malloc(sizeof(char) * (ft_strlen(buf) + 1));

// 	return (0);
// }

// char	*get_flag_here(t_data *data, int i)
// {
// 	int		j;
// 	char	*flag;

// 	j = 0;
// 	while (data->input[i])
// 	{
// 		if (data->input[i] == ' ' && data->input[i + 1] == ' ')
// 		{
// 			while (data->input[i] != ' ')
// 			{
// 				flaf[j] = data->input[i];
// 				i++;
// 				j++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (flag);
// }

// char	*get_name_heredoc()
// {
//     char	*str;
//     int		i;
// 	int		fd;

// 	fd = open("/dev/random", O_RDONLY);
// 	str = NULL;
// 	if (!fd)
// 		return (fprintf(stderr, "problem with fd in here_doc\n"), NULL);
// 	read(fd, str, 14);
// 	i = 1;
// 	str[0] = '.';
// 	while (i < 15)
// 	{
// 		str[i] = (str[i] % 25) + 'a';
// 		i++;
// 	}
//     str[16] = '.';
//     str[17] = 't';
//     str[18] = 'x';
//     str[19] = 't';
//     str[20] = '\0';
// 	close(fd);
// 	return (str);
// }
