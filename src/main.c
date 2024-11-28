/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:27:01 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/29 00:58:30 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern sig_atomic_t g_signal;

static void	main_loop(t_config *config,
				char *input_data, t_node *root, t_data *data);

int	main(int argc, char **argv, char **envp)
{
	char		*input_data;
	t_data		data;
	t_node		*root;
	t_config	config;

	(void)argv;
	if (argc >= 2)
		ft_putendl_fd("warning: command line arguments will be ignored", STDERR_FILENO);
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

int event(void)
{
	return (0);
}

static void	main_loop(t_config *config,
				char *input_data, t_node *root, t_data *data)
{
	while (1)
	{
		g_signal = 0;
		rl_event_hook = event;
		set_idle_handler();
		config->last_exit_status = config->exit_status;
		input_data = readline("minishell$ ");
		if(g_signal != 0)
		{
			config->exit_status = 130;
			continue ;
		}
		if (!input_data)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		if (ft_strlen(input_data) > 0)
			add_history(input_data);
		config->exit_status = lexer(input_data, data, config);
		if (data->token_num == 0 || config->exit_status != EXIT_SUCCESS)
		{
			if (data->token_num == 0)
				config->exit_status = config->last_exit_status;
			free(input_data);
			free_data(data);
			continue ;
		}
		free(input_data);
		assign_token_type(data);
		parser(&root, data, config);
		free_data(data);
		if (g_signal != 0)
			continue ;
		if (config->exit_status != EXIT_SUCCESS)
			continue ;
		config->exit_status
			= run_tree(root, STDIN_FILENO, STDOUT_FILENO, config);
		free_tree(root);
	}
}
