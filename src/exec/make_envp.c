/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 01:59:44 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/17 02:04:04 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exec.h"

char	**make_envp(t_config *config)
{
	char	**envp;
	int		i;
	char	*key_value;

	envp = (char **)malloc(sizeof(char *) * (config->envp_num + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (i < config->envp_num)
	{
		key_value = ft_strjoin(config->envp[i].key, "=");
		if (key_value == NULL)
			return (free_2d(envp), NULL);
		envp[i] = ft_strjoin(key_value, config->envp[i].value);
		free(key_value);
		if (envp[i] == NULL)
			return (free_2d(envp), NULL);
		i++;
	}
	envp[i] = NULL;
	return (envp);
}
