/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:22:20 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/14 23:43:20 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static void	lexer_init(t_data *data, t_lexer_flag *flag);
static void	count_token(const char *input_line, t_data *data, t_lexer_flag *flag);

int	lexer(const char *input_line, t_data *data)
{
	t_lexer_flag	flag;
	int				i;
	int				j;

	count_token(input_line, data, &flag);
	printf("token_num: %d\n", data->token_num);
	if (flag.squote || flag.dquote)
	{
		write(STDERR_FILENO, "syntax error\n", 13);
		return (EXIT_INVALID_INPUT);
	}
	data->token_arr = ft_calloc(data->token_num + 1, sizeof(t_token));
	if (!data->token_arr)
	{
		perror("ft_calloc");
		return (EXIT_FAILURE);
	}
	i = -1;
	j = 0;
	while (input_line[++i])
	{
		if (!is_space(input_line[i]) && sign_len(&input_line[i]) == 0)
		{
			input_line += i;
			i = -1;
			while (input_line[++i])
			{
				if (is_space(input_line[i]) && !flag.dquote && !flag.squote)
					break ;
				else if (sign_len(&input_line[i]) > 0 && !flag.dquote && !flag.squote)
					break ;
				if (input_line[i] == '"' && !flag.squote)
					flag.dquote = !flag.dquote;
				else if (input_line[i] == '\'' && !flag.dquote)
					flag.squote = !flag.squote;
			}
			data->token_arr[j++].token = ft_substr(input_line, 0, i);
			if (!data->token_arr[j - 1].token)
			{
				perror("ft_substr");
				free_data(data);
				return (EXIT_FAILURE);
			}
			input_line += i;
			i = -1;
		}
		else if (sign_len(&input_line[i]) > 0 && !flag.dquote && !flag.squote)
		{
			data->token_arr[j++].token = ft_substr(input_line, i, sign_len(&input_line[i]));
			if (!data->token_arr[j - 1].token)
			{
				perror("ft_substr");
				free_data(data);
				return (EXIT_FAILURE);
			}
			input_line += sign_len((char *)&input_line[i]) + i;
			i = -1;
		}
	}
	return (EXIT_SUCCESS);
}

static void	lexer_init(t_data *data, t_lexer_flag *flag)
{
	data->token_num = 0;
	data->token_arr = NULL;
	flag->dquote = 0;
	flag->squote = 0;
	flag->sep = 1;
}

static void	count_token(const char *input_line,
	t_data *data, t_lexer_flag *flag)
{
	int	i;

	lexer_init(data, flag);
	i = -1;
	while (input_line[++i])
	{
		if ((input_line[i] == '"' && !flag->squote)
			|| (input_line[i] == '\'' && !flag->dquote))
			data->token_num += flip_quote(input_line[i], flag);
		else if (is_space(input_line[i]) && !flag->dquote && !flag->squote)
			flag->sep = 1;
		else if (sign_len(&input_line[i]) > 0
			&& !flag->dquote && !flag->squote)
		{
			data->token_num++;
			i += sign_len(&input_line[i]) - 1;
			flag->sep = 1;
		}
		else if (flag->sep && !is_space(input_line[i]))
		{
			data->token_num++;
			flag->sep = 0;
		}
	}
}

int	main(void)
{
	char		*input_line;
	t_data		data;
	int			i;
	const char	*type[] = {"WORD", "PIPE", "REDIRECT_IN", "REDIRECT_OUT",
		"REDIRECT_HEREDOC", "REDIRECT_APPEND", "PAREN_LEFT",
		"PAREN_RIGHT", "LOGICAL_AND", "LOGICAL_OR"};
	int			status;

	while (1)
	{
		input_line = readline("lexer$ ");
		if (!input_line)
			break ;
		status = lexer(input_line, &data);
		if (status != EXIT_SUCCESS)
			continue ;
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
