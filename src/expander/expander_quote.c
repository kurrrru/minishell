/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 19:57:56 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/12/01 20:23:36 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static int	expander_quote_init(char ***expanded,
				t_lexer_flag *flag, t_config *config, int *i);
static int	join_substr(char **s, const char *word, int end, t_config *config);
static int	join_substr_expand(char **s,
				const char *word, int end, t_config *config);

char	**expander_quote(const char *word, t_config *config)
{
	char			**expanded;
	int				i;
	t_lexer_flag	flag;

	if (expander_quote_init(&expanded, &flag, config, &i) != EXIT_SUCCESS)
		return (NULL);
	while (word[++i])
	{
		if ((word[i] == '\'' && !flag.dquote)
			|| (word[i] == '\"' && !flag.squote))
		{
			if (word[i] == '\'' && !flag.dquote && flag.squote)
				join_substr(&expanded[0], word, i, config);
			else
				join_substr_expand(&expanded[0], word, i, config);
			if (config->exit_status != EXIT_SUCCESS)
				return (free_2d(expanded), NULL);
			flip_quote(word[i], &flag);
			word += i + 1;
			i = -1;
		}
	}
	if (join_substr_expand(&expanded[0], word, i, config) != EXIT_SUCCESS)
		return (free_2d(expanded), NULL);
	return (expanded);
}

static int	expander_quote_init(char ***expanded,
				t_lexer_flag *flag, t_config *config, int *i)
{
	*expanded = ft_calloc(2, sizeof(char *));
	if (!*expanded)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), EXIT_FAILURE);
	}
	(*expanded)[0] = ft_strdup("");
	if (!(*expanded)[0])
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), free(expanded), EXIT_FAILURE);
	}
	flag->dquote = 0;
	flag->squote = 0;
	*i = -1;
	return (EXIT_SUCCESS);
}

static int	join_substr(char **s, const char *word, int end, t_config *config)
{
	char	*sub;
	char	*joined;

	sub = ft_substr(word, 0, end);
	if (!sub)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), EXIT_FAILURE);
	}
	joined = ft_strjoin(*s, sub);
	if (!joined)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), free(sub), EXIT_FAILURE);
	}
	free(*s);
	*s = joined;
	return (free(sub), EXIT_SUCCESS);
}

static int	join_substr_expand(char **s,
				const char *word, int end, t_config *config)
{
	char	*sub;
	char	*expanded;
	char	*joined;

	sub = ft_substr(word, 0, end);
	if (!sub)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), EXIT_FAILURE);
	}
	expanded = expand_env(sub, config);
	if (!expanded)
		return (free(sub), EXIT_FAILURE);
	joined = ft_strjoin(*s, expanded);
	if (!joined)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), free(sub), free(expanded), EXIT_FAILURE);
	}
	free(*s);
	*s = joined;
	return (free(sub), free(expanded), EXIT_SUCCESS);
}
