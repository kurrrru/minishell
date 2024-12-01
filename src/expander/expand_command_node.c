/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command_node.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkawaguc <nkawaguc@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 20:04:34 by nkawaguc          #+#    #+#             */
/*   Updated: 2024/11/30 17:31:33 by nkawaguc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/expander.h"

static int	expand_command_and_arg(t_node *node, t_config *config);
static int	expand_redirect(t_node *node, t_config *config);
static int	replace_by_expanded(t_node *node, char ***expanded_arr);
static int	calc_capacity(t_node *node, char ***expanded_arr);

int	expand_command_node(t_node *node, t_config *config)
{
	config->exit_status = expand_command_and_arg(node, config);
	if (config->exit_status != EXIT_SUCCESS)
		return (config->exit_status);
	config->exit_status = expand_redirect(node, config);
	if (config->exit_status != EXIT_SUCCESS)
		return (config->exit_status);
	return (EXIT_SUCCESS);
}

static int	expand_command_and_arg(t_node *node, t_config *config)
{
	int		i;
	char	***expanded_arr;

	if (!node->command)
		return (EXIT_SUCCESS);
	expanded_arr = ft_calloc(node->arg_num + 1, sizeof(char **));
	if (!expanded_arr)
		return (perror("ft_calloc"), EXIT_FAILURE);
	expanded_arr[0] = expander(node->command, config);
	if (!expanded_arr[0])
		return (free_3d(expanded_arr), EXIT_FAILURE);
	i = -1;
	while (++i < node->arg_num)
	{
		expanded_arr[i + 1] = expander(node->argv[i], config);
		if (!expanded_arr[i + 1])
			return (free_3d(expanded_arr), EXIT_FAILURE);
	}
	free(node->command);
	free_2d(node->argv);
	return (replace_by_expanded(node, expanded_arr));
}

static int	expand_redirect(t_node *node, t_config *config)
{
	int		i;
	char	**expanded;

	i = -1;
	while (++i < node->redirect_num)
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
	}
	return (EXIT_SUCCESS);
}

static int	calc_capacity(t_node *node, char ***expanded_arr)
{
	int		i;
	int		capacity;

	capacity = expand_len(expanded_arr[0]);
	i = 0;
	while (++i < node->arg_num + 1)
		capacity += expand_len(expanded_arr[i]);
	return (capacity);
}

static int	replace_by_expanded(t_node *node, char ***expanded_arr)
{
	int		i;
	int		j;
	int		k;

	node->command = expanded_arr[0][0];
	node->arg_capacity = calc_capacity(node, expanded_arr);
	node->argv = ft_calloc(node->arg_capacity + 1, sizeof(char *));
	if (!node->argv)
		return (perror("ft_calloc"), free_3d(expanded_arr), EXIT_FAILURE);
	i = 0;
	k = 1;
	while (expanded_arr[0][k])
		node->argv[i++] = expanded_arr[0][k++];
	free(expanded_arr[0]);
	j = 0;
	while (++j < node->arg_num + 1)
	{
		k = 0;
		while (expanded_arr[j][k])
			node->argv[i++] = expanded_arr[j][k++];
		free(expanded_arr[j]);
	}
	node->arg_num = i;
	return (free(expanded_arr), EXIT_SUCCESS);
}
