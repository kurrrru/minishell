/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 14:24:25 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/16 21:28:54 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../../include/parser.h"
// #include "../../include/lexer.h"
// #include "../../include/config.h"

// void	dump_node(t_node *node, int depth)
// {
// 	if (node == NULL)
// 		return;
// 	if (node->type == NODE_COMMAND)
// 	{
// 		for (int i = 0; i < depth; i++)
// 			ft_putstr_fd("  ", STDOUT_FILENO);
// 		ft_putstr_fd("command: ", STDOUT_FILENO);
// 		ft_putendl_fd(node->command, STDOUT_FILENO);
// 		for (int i = 0; i < node->arg_num; i++)
// 		{
// 			for (int j = 0; j < depth; j++)
// 				ft_putstr_fd("  ", STDOUT_FILENO);
// 			ft_putstr_fd("arg: ", STDOUT_FILENO);
// 			ft_putendl_fd(node->argv[i], STDOUT_FILENO);
// 		}
// 		for (int i = 0; i < node->redirect_num; i++)
// 		{
// 			for (int j = 0; j < depth; j++)
// 				ft_putstr_fd("  ", STDOUT_FILENO);
// 			ft_putstr_fd("redirect: ", STDOUT_FILENO);
// 			ft_putnbr_fd(node->redirect[i].type, STDOUT_FILENO);
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 			ft_putendl_fd(node->redirect[i].file, STDOUT_FILENO);
// 		}
// 		for (int i = 0; i < depth; i++)
// 			ft_putstr_fd("  ", STDOUT_FILENO);
// 		ft_putstr_fd("depth: ", STDOUT_FILENO);
// 		ft_putnbr_fd(depth, STDOUT_FILENO);
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 	}
// 	else
// 	{
// 		char *connector[3] = {"PIPE", "LOGICAL_AND", "LOGICAL_OR"};
// 		dump_node(node->left, depth + 1);
// 		for (int i = 0; i < depth; i++)
// 			ft_putstr_fd("  ", STDOUT_FILENO);
// 		ft_putstr_fd("connector: ", STDOUT_FILENO);
// 		ft_putendl_fd(connector[node->type], STDOUT_FILENO);
// 		for (int i = 0; i < depth; i++)
// 			ft_putstr_fd("  ", STDOUT_FILENO);
// 		ft_putstr_fd("depth: ", STDOUT_FILENO);
// 		ft_putnbr_fd(depth, STDOUT_FILENO);
// 		ft_putstr_fd("\n", STDOUT_FILENO);
// 		for (int i = 0; i < node->redirect_num; i++)
// 		{
// 			for (int j = 0; j < depth; j++)
// 				ft_putstr_fd("  ", STDOUT_FILENO);
// 			ft_putstr_fd("redirect: ", STDOUT_FILENO);
// 			ft_putnbr_fd(node->redirect[i].type, STDOUT_FILENO);
// 			ft_putstr_fd(" ", STDOUT_FILENO);
// 			ft_putendl_fd(node->redirect[i].file, STDOUT_FILENO);
// 		}
// 		dump_node(node->right, depth + 1);
// 	}
// }

// void dump_tree(t_node *root)
// {
// 	dump_node(root, 0);
// }

// int	main(int argc, char **argv, char **envp)
// {
// 	char		*input_data;
// 	t_data		data;
// 	t_node		*root;
// 	t_config	config;

// 	(void)argc;
// 	(void)argv;
// 	init_config(&config, envp);
// 	while (1)
// 	{
// 		input_data = readline("parser$ ");
// 		add_history(input_data);
// 		if (!input_data)
// 			break;
// 		config.exit_status = lexer(input_data, &data);
// 		if (config.exit_status != EXIT_SUCCESS)
// 			continue;
// 		parser(&root, &data, &config);
// 		free_data(&data);
// 		if (config.exit_status != EXIT_SUCCESS)
// 		{
// 			ft_putstr_fd("exit_status: ", STDOUT_FILENO);
// 			ft_putnbr_fd(config.exit_status, STDOUT_FILENO);
// 			ft_putstr_fd("\n", STDOUT_FILENO);
// 			continue;
// 		}
// 		dump_tree(root);
// 		free_tree(root);
// 		free(input_data);
// 	}
// 	free_config(&config);
// 	return (EXIT_SUCCESS);
// }
