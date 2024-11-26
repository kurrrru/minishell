/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:00:30 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 20:50:28 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

char	**expander(const char *word, t_config *config)
{
	char	*env_expanded;
	char	**expanded;
	int		i;

	printf("expander\n");
	env_expanded = expand_env(word, config);
	if (!env_expanded)
		return (NULL);
	printf("expand_env done\n");
	expanded = expand_wildcard(env_expanded, config);
	free(env_expanded);
	if (!expanded)
		return (NULL);
	printf("expand_wildcard done\n");
	i = -1;
	while (expanded[++i])
		del_quote(expanded[i]);
	printf("del_quote done\n");
	return (expanded);
}
