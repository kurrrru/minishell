/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:00:30 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/27 00:06:33 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

char	**expander(const char *word, t_config *config)
{
	char	*env_expanded;
	char	**expanded;
	int		i;

	env_expanded = expand_env(word, config);
	if (!env_expanded)
		return (NULL);
	expanded = expand_wildcard(env_expanded, config);
	free(env_expanded);
	if (!expanded)
		return (NULL);
	i = -1;
	while (expanded[++i])
		del_quote(expanded[i]);
	return (expanded);
}
