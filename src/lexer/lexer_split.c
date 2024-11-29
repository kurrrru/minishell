/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 22:22:20 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/15 13:48:30 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static void	lexer_init(t_data *data, t_lexer_flag *flag);
static void	count_token(const char *input_line,
				t_data *data, t_lexer_flag *flag);
static int	copy_word(const char **input_line,
				t_token *token, int *i, t_lexer_flag *flag);
static int	split_token(const char *input_line,
				t_data *data, t_lexer_flag *flag);

int	lexer_split(const char *input_line, t_data *data)
{
	t_lexer_flag	flag;

	count_token(input_line, data, &flag);
	if (flag.squote || flag.dquote)
	{
		if (flag.dquote)
			ft_putendl_fd("Syntax error: unmatched `\"'", STDERR_FILENO);
		else
			ft_putendl_fd("Syntax error: unmatched `''", STDERR_FILENO);
		return (EXIT_INVALID_INPUT);
	}
	if(data->token_num == 0)
		return (EXIT_SUCCESS);
	data->token_arr = ft_calloc(data->token_num + 1, sizeof(t_token));
	if (!data->token_arr)
	{
		perror("ft_calloc");
		return (EXIT_FAILURE);
	}
	return (split_token(input_line, data, &flag));
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

static int	copy_word(const char **input_line,
	t_token *token, int *i, t_lexer_flag *flag)
{
	*input_line += *i;
	*i = -1;
	while ((*input_line)[++(*i)])
	{
		if (is_space((*input_line)[*i]) && !flag->dquote && !flag->squote)
			break ;
		else if (sign_len(&(*input_line)[*i]) > 0
			&& !flag->dquote && !flag->squote)
			break ;
		if ((*input_line)[*i] == '"' && !flag->squote)
			flag->dquote = !flag->dquote;
		else if ((*input_line)[*i] == '\'' && !flag->dquote)
			flag->squote = !flag->squote;
	}
	token->token = ft_substr(*input_line, 0, *i);
	if (!token->token)
	{
		perror("ft_substr");
		return (EXIT_FAILURE);
	}
	*input_line += *i;
	*i = -1;
	return (EXIT_SUCCESS);
}

static int	split_token(const char *input_line,
	t_data *data, t_lexer_flag *flag)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (input_line[++i])
	{
		if (!is_space(input_line[i]) && sign_len(&input_line[i]) == 0)
		{
			if (copy_word(&input_line, &data->token_arr[j++], &i, flag)
				!= EXIT_SUCCESS)
				return (free_data(data), EXIT_FAILURE);
		}
		else if (sign_len(&input_line[i]) > 0 && !flag->dquote && !flag->squote)
		{
			data->token_arr[j++].token
				= ft_substr(input_line, i, sign_len(&input_line[i]));
			if (!data->token_arr[j - 1].token)
				return (perror("ft_substr"), free_data(data), EXIT_FAILURE);
			input_line += sign_len((char *)&input_line[i]) + i;
			i = -1;
		}
	}
	return (EXIT_SUCCESS);
}
