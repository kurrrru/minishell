/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:22:20 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/05 23:14:04 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static int	is_space(char c);
static int	sign_len(char *s);

void	lexer(const char *input_line, t_data *data)
{
	int		dquote;
	int		squote;
	int		sep;
	int		i;
	int		j;

	dquote = 0;
	squote = 0;
	sep = 1;
	i = -1;
	data->token_num = 0;
	while (input_line[++i])
	{
		if (input_line[i] == '"' && !squote)
		{
			if (!dquote && sep)
			{
				data->token_num++;
				sep = 0;
			}
			dquote = !dquote;
		}
		else if (input_line[i] == '\'' && !dquote)
		{
			if (!squote && sep)
			{
				data->token_num++;
				sep = 0;
			}
			squote = !squote;
		}
		else if (is_space(input_line[i]) && !dquote && !squote)
			sep = 1;
		else if (sign_len((char *)&input_line[i]) > 0 && !dquote && !squote)
		{
			data->token_num++;
			i += sign_len((char *)&input_line[i]) - 1;
			sep = 1;
		}
		else if (sep && !is_space(input_line[i]))
		{
			data->token_num++;
			sep = 0;
		}
	}
	if (squote || dquote)
	{
		write(STDERR_FILENO, "syntax error\n", 13);
		exit(EXIT_FAILURE);
	}
	data->token_arr = (t_token *)xmalloc(sizeof(t_token) * data->token_num + 1);
	i = -1;
	j = 0;
	while (input_line[++i])
	{
		if (!is_space(input_line[i]) && sign_len((char *)&input_line[i]) == 0)
		{
			input_line += i;
			i = -1;
			while (input_line[++i])
			{
				if (is_space(input_line[i]) && !dquote && !squote)
					break ;
				else if (sign_len((char *)&input_line[i]) > 0 && !dquote && !squote)
					break ;
				if (input_line[i] == '"' && !squote)
					dquote = !dquote;
				else if (input_line[i] == '\'' && !dquote)
					squote = !squote;
			}
			data->token_arr[j++].token = xstrndup(input_line, i);
			input_line += i;
			i = -1;
		}
		else if (sign_len((char *)&input_line[i]) > 0 && !dquote && !squote)
		{
			data->token_arr[j++].token = xstrndup((char *)&input_line[i], sign_len((char *)&input_line[i]));
			input_line += sign_len((char *)&input_line[i]) + i;
			i = -1;
		}
	}
}

static int is_space(char c)
{
	return (c == ' ' || c == '\t');
}

static int	sign_len(char *s)
{
	if (ft_strncmp(s, "&&", 2) == 0 || ft_strncmp(s, "||", 2) == 0 || ft_strncmp(s, ">>", 2) == 0 || ft_strncmp(s, "<<", 2) == 0)
		return (2);
	if (s[0] == '|' || s[0] == '<' || s[0] == '>' || s[0] == '(' || s[0] == ')')
		return (1);
	return (0);
}

int	main(void)
{
	char		*input_line;
	t_data		data;
	int			i;
	char		*type[] = {"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT", "REDIRECT_HEREDOC", "REDIRECT_APPEND", "PAREN_LEFT", "PAREN_RIGHT", "LOGICAL_AND", "LOGICAL_OR"};

	while (1)
	{
		input_line = readline("lexer$ ");
		if (!input_line)
			break ;
		lexer(input_line, &data);
		assign_token_type(&data);
		i = -1;
		while (++i < data.token_num)
		{
			printf("token: [%s]\n", data.token_arr[i].token);
			printf("type: %s\n", type[data.token_arr[i].type]);
		}
	}
	return (EXIT_SUCCESS);
}
