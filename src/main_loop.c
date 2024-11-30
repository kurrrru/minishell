/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 10:31:02 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 10:45:43 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern sig_atomic_t	g_signal;

static int	event(void);
static char	*get_input_data(t_config *config);

void	main_loop(t_config *config,
				char *input_data, t_node *root, t_data *data)
{
	while (1)
	{
		input_data = get_input_data(config);
		if (g_signal != 0)
			continue ;
		if (!input_data)
			break ;
		config->exit_status = lexer(input_data, data, config);
		free(input_data);
		if (data->token_num == 0 || config->exit_status != EXIT_SUCCESS)
		{
			if (data->token_num == 0)
				config->exit_status = config->last_exit_status;
			continue ;
		}
		parser(&root, data, config);
		free_data(data);
		if (g_signal != 0 || config->exit_status != EXIT_SUCCESS)
			continue ;
		config->exit_status
			= run_tree(root, STDIN_FILENO, STDOUT_FILENO, config);
		free_tree(root);
	}
}

static int	event(void)
{
	return (0);
}

static char	*get_input_data(t_config *config)
{
	char	*input_data;

	g_signal = 0;
	rl_event_hook = event;
	set_idle_handler();
	config->last_exit_status = config->exit_status;
	input_data = readline("minishell$ ");
	if (g_signal == 0 && input_data && ft_strlen(input_data) > 0)
		add_history(input_data);
	if (g_signal == SIGINT)
		config->exit_status = 130;
	if (!input_data)
		ft_putendl_fd("exit", STDERR_FILENO);
	return (input_data);
}
