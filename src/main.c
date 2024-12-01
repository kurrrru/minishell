/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:27:01 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 10:32:13 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input_data;
	t_data		data;
	t_node		*root;
	t_config	config;

	(void)argv;
	if (argc >= 2)
		ft_putendl_fd("warning: command line arguments \
will be ignored", STDERR_FILENO);
	if (init_config(&config, envp) == EXIT_FAILURE)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	input_data = NULL;
	root = NULL;
	main_loop(&config, input_data, root, &data);
	free_config(&config);
	return (config.last_exit_status);
}
