/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpotilli <tpotilli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:37:41 by vsozonof          #+#    #+#             */
/*   Updated: 2024/02/20 09:26:41 by tpotilli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int argc, char **argv, char **env)
// {
//     t_shell     shell;
//     ft_parse_envs_to_lst(&envs, env); // transform env to linked list
//     shell.tmpfile = "path to tmpfile";
//     while (1)
//     {
//         char *buf = readline("bash: ");
//         add_history(buf);
//         shell.std_in = dup(0);
//         shell.std_out = dup(1);
//         shell.f_in = dup(0);
//         shell.f_out = dup(1);
//         /* Token is represented by linked list. "cat << eof" translates into "cat" -> ">>" -> "eof",
//         with token pointing to "cat" */
//         t_token *token = parse_buffer(buf); // parse_buffer will return pointer to the first token
//         ft_execute_token(shell, token, env);
//         free(buf);
//     }
// }

char	*get_name_heredoc(void)
{
	char		*str;
	int			i;
	int			fd;

	fd = open("/dev/urandom", O_RDONLY);
	str = malloc(sizeof(char) * 21);
	if (fd == -1)
		return (fprintf(stderr, "problem with fd in here_doc\n"), NULL);
	read(fd, str, 14);
	i = 0;
	while (i <= 15)
	{
		str[i] = (str[i] % 25) + 'a';
		i++;
	}
	str[16] = '.';
	str[17] = 't';
	str[18] = 'x';
	str[19] = 't';
	str[20] = '\0';
	close(fd);
	return (str);
}

char	*extract_delimiter(char *input)
{
	int	i;
	int	c;

	c = ((i = 0));
	while (input[i])
	{
		if (input[i] == '<')
		{
			i += 2;
			break ;
		}
		i++;
	}
	while (input[i] && ft_is_whitespace(input[i]))
		i++;
	c = i;
	while (input[c] && !ft_is_whitespace(input[c]))
		c++;
	return (ft_substr(input, i, (c - i)));
}

int	heredoc_handler(char *delimiter, t_data *data)
{
	char	*input;
	int		fd;

	data->heredoc_fname = get_name_heredoc();
	fd = open(data->heredoc_fname, O_APPEND | O_WRONLY | O_CREAT, 0644);
	while (42)
	{
		input = readline("> ");
		if (!ft_strncmp(input, delimiter, ft_strlen(delimiter)))
		{
			free(input);
			break ;
		}
		ft_putstr_fd(input, fd);
		write(fd, "\n", 1);
		free(input);
	}
	return (fd);
}

int	main_here_doc(t_data *data)
{
	char	*delimiter;
	int		i;
	int		c;
	int		fd;

	c = ((i = 0));
	printf("HEREDOC DETECTED %i\n", data->nb_here_doc);
	if (data->n_cmds > 1)
	{
		while (data->cmds[c])
		{
			if (!hdoc_counter(data->cmds[c]))
				c++;
			delimiter = extract_delimiter(data->cmds[c]);
			fd = heredoc_handler(delimiter, data);
			data->cmds[c] = input_reformatter(data->cmds[c], data);
			free(delimiter);
		}
	}
	else
	{
		while (i < data->nb_here_doc)
		{
			delimiter = extract_delimiter(data->input);
			fd = heredoc_handler(delimiter, data);
			data->input = input_reformatter(data->input, data);
			free(delimiter);
			i++;
		}
	}
	close(fd);
	return (0);
}

char	*input_reformatter(char *str, t_data *data)
{
	int	i;
	int	start;
	int	end;

	i = 0;
	while (str[i])
	{
		if (str[i] == '<' && str[i + 1] == '<')
		{
			start = i;
			i += 2;
			break ;
		}
		i++;
	}
	while (str[i] && ft_is_whitespace(str[i]))
		i++;
	while (str[i] && !ft_is_whitespace(str[i]))
		i++;
	end = i;
	return (replace_token_with_filename(str, data, start, end));
}

char	*replace_token_with_filename(char *str, t_data *data, int start, int end)
{
	data->head = ft_substr(str, 0, start);
	printf("head -> %s\n", data->head);
	data->tail = ft_substr(str, end, ft_strlen(str));
	printf("tail -> %s\n", data->tail);
	free(str);
	str = strjoin_and_free(data->head, data->heredoc_fname);
	printf("str = %s\n", str);
	str = strjoin_and_free(str, data->tail);
	printf("input = %s\n", str);
	return (str);
}
