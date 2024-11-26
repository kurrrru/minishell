/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:27:01 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 15:13:35 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	main_loop(t_config *config,
				char *input_data, t_node *root, t_data *data);

int	main(int argc, char **argv, char **envp)
{
	char		*input_data;
	t_data		data;
	t_node		*root;
	t_config	config;

	(void)argc;
	(void)argv;
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

static void	main_loop(t_config *config,
				char *input_data, t_node *root, t_data *data)
{
	while (1)
	{
		config->last_exit_status = config->exit_status;
		input_data = readline("minishell$ ");
		add_history(input_data);
		if (!input_data)
		{
			ft_putendl_fd("exit", STDERR_FILENO);
			break ;
		}
		config->exit_status = lexer(input_data, data, config);
		if (ft_strlen(input_data) == 0 || config->exit_status != EXIT_SUCCESS)
		{
			free(input_data);
			continue ;
		}
		free(input_data);
		assign_token_type(data);
		parser(&root, data, config);
		free_data(data);
		if (config->exit_status != EXIT_SUCCESS)
			continue ;
		config->exit_status
			= run_tree(root, STDIN_FILENO, STDOUT_FILENO, config);
		free_tree(root);
	}
}
