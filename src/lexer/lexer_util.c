/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_util.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 22:43:13 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/14 23:46:10 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

int	is_space(char c)
{
	return (c == ' ' || c == '\t');
}

int	sign_len(const char *s)
{
	if (ft_strncmp(s, "&&", 2) == 0 || ft_strncmp(s, "||", 2) == 0
		|| ft_strncmp(s, ">>", 2) == 0 || ft_strncmp(s, "<<", 2) == 0)
		return (2);
	if (s[0] == '|' || s[0] == '<' || s[0] == '>' || s[0] == '(' || s[0] == ')')
		return (1);
	return (0);
}

int	flip_quote(const char quote, t_lexer_flag *flag)
{
	int	token_num_diff;

	token_num_diff = 0;
	if (quote == '"' && !flag->squote)
	{
		if (!flag->dquote && flag->sep)
		{
			flag->sep = 0;
			token_num_diff = 1;
		}
		(flag->dquote) = !(flag->dquote);
	}
	else if (quote == '\'' && !flag->dquote)
	{
		if (!flag->squote && flag->sep)
		{
			flag->sep = 0;
			token_num_diff = 1;
		}
		(flag->squote) = !(flag->squote);
	}
	return (token_num_diff);
}
