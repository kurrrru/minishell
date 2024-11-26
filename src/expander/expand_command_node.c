/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:04:34 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/26 21:12:45 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static int	expand_command_and_arg(t_node *node, t_config *config);
static int	expand_redirect(t_node *node, t_config *config);

int	expand_command_node(t_node *node, t_config *config)
{
	printf("expand_command_node\n");
	config->exit_status = expand_command_and_arg(node, config);
	if (config->exit_status != EXIT_SUCCESS)
		return (config->exit_status);
	printf("expand_command_and_arg done\n");
	config->exit_status = expand_redirect(node, config);
	if (config->exit_status != EXIT_SUCCESS)
		return (config->exit_status);
	return (EXIT_SUCCESS);
}

static int	expand_command_and_arg(t_node *node, t_config *config)
{
	int		i;
	int		j;
	int		k;
	char	***expanded_arr;

	if (!node->command)
		return (EXIT_SUCCESS);
	expanded_arr = ft_calloc(node->arg_num + 1, sizeof(char **));
	if (!expanded_arr)
	{
		perror("ft_calloc");
		return (EXIT_FAILURE);
	}
	expanded_arr[0] = expander(node->command, config);
	if (!expanded_arr[0])
	{
		free_3d(expanded_arr);
		return (EXIT_FAILURE);
	}
	printf("Here\n");
	i = -1;
	while (++i < node->arg_num)
	{
		expanded_arr[i + 1] = expander(node->argv[i], config);
		if (!expanded_arr[i + 1])
		{
			free_3d(expanded_arr);
			return (EXIT_FAILURE);
		}
	}
	free(node->command);
	free_2d(node->argv);
	node->command = expanded_arr[0][0];
	node->arg_capacity = expand_len(expanded_arr[0]);
	i = -1;
	while (++i < node->arg_num)
	{
		node->arg_capacity += expand_len(expanded_arr[i + 1]);
	}
	node->argv = ft_calloc(node->arg_capacity + 1, sizeof(char *));
	if (!node->argv)
	{
		perror("ft_calloc");
		free_3d(expanded_arr);
		return (EXIT_FAILURE);
	}
	i = 0;
	j = 0;
	k = 1;
	while (expanded_arr[0][k])
	{
		node->argv[i] = expanded_arr[0][k];
		i++;
		k++;
	}
	free(expanded_arr[0]);
	printf("node->arg_num: %d\n", node->arg_num);
	printf("(i,j,k): (%d,%d,%d)\n", i, j, k);
	printf("node->capacity: %d\n", node->arg_capacity);
	while (j < node->arg_num)
	{
		k = 0;
		while (expanded_arr[j + 1][k])
		{
			node->argv[i] = expanded_arr[j + 1][k];
			printf("node->argv[%d]: %s\n", i, node->argv[i]);
			i++;
			k++;
		}
		j++;
		free(expanded_arr[j]);
	}
	free(expanded_arr);
	node->arg_num = i;
	return (EXIT_SUCCESS);
}

static int	expand_redirect(t_node *node, t_config *config)
{
	int		i;
	char	**expanded;

	printf("expand_redirect\n");
	printf("node->redirect_num: %d\n", node->redirect_num);
	i = 0;
	while (i < node->redirect_num)
	{
		if (node->redirect[i].type == HEREDOC)
			continue ;
		expanded = expander(node->redirect[i].file, config);
		if (expand_len(expanded) != 1)
		{
			ft_putstr_fd(node->redirect[i].file, STDERR_FILENO);
			ft_putendl_fd(": ambiguous redirect", STDERR_FILENO);
			free_2d(expanded);
			return (EXIT_FAILURE);
		}
		free(node->redirect[i].file);
		node->redirect[i].file = expanded[0];
		free(expanded);
		i++;
	}
	return (EXIT_SUCCESS);
}
