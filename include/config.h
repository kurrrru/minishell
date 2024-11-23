/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 13:13:01 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/15 13:19:35 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_H
# define CONFIG_H

# include "include.h"
# include "macro.h"

typedef struct s_env
{
	char	*key;
	char	*value;
}	t_env;

typedef struct s_config
{
	int		exit_status;
	t_env	*envp;
	int		envp_num;
	int		envp_capacity;
}	t_config;

int		init_config(t_config *config, char **envp);
void	free_config(t_config *config);
char	**make_envp(t_config *config);

#endif
