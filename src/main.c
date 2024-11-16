/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 22:27:01 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/16 22:31:14 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int main(int argc, char **argv, char **envp)
{
	char *input_data;
	t_data data;
	t_node *root;
	t_config config;

	(void)argc;
	(void)argv;
	if (init_config(&config, envp) == EXIT_FAILURE)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (isatty(STDERR_FILENO))
			input_data = readline("minishell$ ");
		else
			input_data = readline(NULL);
		add_history(input_data);
		if (!input_data)
		{
			if (isatty(STDERR_FILENO))
				write(2, "exit\n", 5);
			break;
		}
		config.exit_status = lexer(input_data, &data);
		free(input_data);
		if (config.exit_status != 0)
			continue ;
		assign_token_type(&data);
		parser(&root, &data, &config);
		free_data(&data);
		if (config.exit_status != EXIT_SUCCESS)
			continue ;
		// dump_tree(root);
		config.exit_status = run_tree(root, 0, 1, &config);
		free_tree(root);
		printf("exit status: %d\n", config.exit_status);
	}
	free_config(&config);
}
