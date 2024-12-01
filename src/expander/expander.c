/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:00:30 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/12/01 19:58:40 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static char	**expander_no_quote(const char *word, t_config *config);

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
	return (expanded);
}
