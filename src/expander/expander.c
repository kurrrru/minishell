/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:00:30 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/12/01 19:56:20 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static char	**expander_no_quote(const char *word, t_config *config);
static char	**expander_quote(const char *word, t_config *config);
static char	*join_substr(const char *s, const char *word, int end, t_config *config);
static char	*join_substr_expand(const char *s, const char *word, int end, t_config *config);

char	**expander(const char *word, t_config *config)
{
	if (!ft_strchr(word, '\'') && !ft_strchr(word, '\"'))
		return (expander_no_quote(word, config));
	else
		return (expander_quote(word, config));
}

static char	**expander_no_quote(const char *word, t_config *config)
{
	char	*env_expanded;
	char	**expanded;

	env_expanded = expand_env(word, config);
	if (!env_expanded)
		return (NULL);
	expanded = expand_wildcard(env_expanded, config);
	free(env_expanded);
	if (!expanded)
		return (NULL);
	// i = -1;
	// while (expanded[++i])
	// 	del_quote(expanded[i]);
	return (expanded);
}

static char	**expander_quote(const char *word, t_config *config)
{
	char			**expanded;
	char			*joined;
	int				i;
	t_lexer_flag	flag;

	expanded = ft_calloc(2, sizeof(char *));
	if (!expanded)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), NULL);
	}
	expanded[0] = ft_strdup("");
	if (!expanded[0])
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), NULL);
	}
	flag.dquote = 0;
	flag.squote = 0;
	i = -1;
	while (word[++i])
	{
		if ((word[i] == '\'' && !flag.dquote) || (word[i] == '\"' && !flag.squote))
		{
			if (word[i] == '\'' && !flag.dquote && flag.squote)
				joined = join_substr(expanded[0], word, i, config);
			else
				joined = join_substr_expand(expanded[0], word, i, config);
			if (!joined)
				return (free_2d(expanded), NULL);
			flip_quote(word[i], &flag);
			free(expanded[0]);
			expanded[0] = joined;
			word += i + 1;
			i = -1;
		}
	}
	joined = join_substr_expand(expanded[0], word, i, config);
	if (!joined)
		return (free_2d(expanded), NULL);
	free(expanded[0]);
	expanded[0] = joined;
	return (expanded);
}

static char	*join_substr(const char *s, const char *word, int end, t_config *config)
{
	char	*sub;
	char	*joined;

	sub = ft_substr(word, 0, end);
	if (!sub)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), NULL);
	}
	joined = ft_strjoin(s, sub);
	if (!joined)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), NULL);
	}
	free(sub);
	return (joined);
}

static char	*join_substr_expand(const char *s, const char *word, int end, t_config *config)
{
	char	*sub;
	char	*expanded;
	char	*joined;

	sub = ft_substr(word, 0, end);
	if (!sub)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), NULL);
	}
	expanded = expand_env(sub, config);
	if (!expanded)
	{
		free(sub);
		return (NULL);
	}
	joined = ft_strjoin(s, expanded);
	if (!joined)
	{
		config->exit_status = EXIT_FAILURE;
		return (perror("malloc"), NULL);
	}
	free(sub);
	free(expanded);
	return (joined);
}
