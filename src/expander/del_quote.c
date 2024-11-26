/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 00:25:17 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 19:32:35 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "expander.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void	append_segment(char *word, int *j, int *i, char quote);

/*
Unclosed quote is dealt with in lexer, so we don't have to worry about it here.
*/
void	del_quote(char *word)
{
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	while (word[i])
	{
		if (word[i] == '\'' || word[i] == '"')
		{
			quote = word[i];
			i++;
			append_segment(word, &j, &i, quote);
		}
		else
		{
			word[j] = word[i];
			j++;
		}
		i++;
	}
	word[j] = '\0';
}

static void	append_segment(char *word, int *i_dst, int *i_src, char quote)
{
	int		i;

	i = *i_src;
	while (word[i] && word[i] != quote)
	{
		word[*i_dst] = word[i];
		(*i_dst)++;
		i++;
	}
	*i_src = i;
}
