/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:59:44 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/24 20:36:53 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

char	**make_envp(t_config *config)
{
	char	**envp;
	int		i;
	int		j;
	char	*key_value;

	envp = (char **)malloc(sizeof(char *) * (config->envp_num + 1));
	if (envp == NULL)
		return (NULL);
	i = -1;
	j = -1;
	while (++i < config->envp_num)
	{
		if (config->envp[i].key && config->envp[i].value)
		{
			key_value = ft_strjoin(config->envp[i].key, "=");
			if (key_value == NULL)
				return (free_2d(envp), NULL);
			envp[++j] = ft_strjoin(key_value, config->envp[i].value);
			free(key_value);
			if (envp[j] == NULL)
				return (free_2d(envp), NULL);
		}
	}
	envp[++j] = NULL;
	return (envp);
}
