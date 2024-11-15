/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:15:07 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/15 13:15:14 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/config.h"

void	free_config(t_config *config)
{
	int	i;

	i = 0;
	while (i < config->envp_num)
	{
		free(config->envp[i].key);
		free(config->envp[i].value);
		i++;
	}
	free(config->envp);
}
